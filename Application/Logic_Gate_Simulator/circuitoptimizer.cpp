#include "circuitoptimizer.h"
#include "allgates.h"
#include <cmath>

int CircuitOptimizer::minterm[MAX][MAX];
int CircuitOptimizer::mask[MAX][MAX];// mask of minterm
int CircuitOptimizer::used[MAX][MAX];// minterm used
int CircuitOptimizer::result[MAX];// results
int CircuitOptimizer::primmask[MAX];// mask for prime implicants
int CircuitOptimizer::prim[MAX];// prime implicant
int CircuitOptimizer::wprim[MAX];// essential prime implicant (TRUE/FALSE)
int CircuitOptimizer::nwprim[MAX];// needed not essential prime implicant

CircuitOptimizer::CircuitOptimizer()
{
}

std::vector<Gate*> CircuitOptimizer::Optimize(std::vector<Gate*>& gates)
{
    size_t numInputNodes = 0;
    TruthTable tt;
    if ( !TruthTableFromCircuit( gates, tt, numInputNodes ) )
        return gates;

    BooleanExpression expression;
    if ( !OptimizedBooleanAlgebraFromTruthTable( numInputNodes, tt, expression ) )
        return gates;

    return CuircuitFromBooleanAlgebra(expression, gates);
}

bool CircuitOptimizer::TruthTableFromCircuit(std::vector<Gate*>& gates, TruthTable& table, size_t& numInputNodes)
{
    //Need to get all input nodes that are not connected & all output nodes that are not connected
    std::vector<Node*> inputNodes;
    std::vector<Node*> outputNodes;
    for (Gate* g : gates)
    {
        g->GetDisconnectedInputNodes(inputNodes);
        g->GetDisconnectedOutputNodes(outputNodes);
    }

    //Check what happens when input values are changed
    numInputNodes = inputNodes.size();

    //Nothing to optimise
    if (numInputNodes < 2 || numInputNodes == 0 || outputNodes.size() == 0)
        return false;

    const int size = pow(2, numInputNodes);
    for (int i = 0; i < size; i++)
    {
        table.push_back(RunOfGates());

        const std::string bin = DecimalToBinaryString(i, numInputNodes);
        for (size_t iNode = 0; iNode < bin.length(); iNode++)
        {
            const bool bIn = bin[iNode] == '0' ? true : false;
            table[i].in.push_back(bIn);
            inputNodes[iNode]->SetValue(bIn);
        }

        table[i].result = outputNodes[0]->GetValue();
    }

    return true;
}

/*
void CircuitOptimizer::GateRun(TruthTable& inputRunResults, std::vector<Node*>& inputNodes, Node*& outputNode,
                               const size_t numInputNodes, std::vector<Gate*>& gates)
{
    for (int index = 0; index < inputRunResults.size(); index++)
    {
        //Run it twice just to be sure. can probably remove this after testing
        for (int x = 0; x < 2; x++)
        {
            for (size_t iNode = 0; iNode < numInputNodes; iNode++)
            {
                inputNodes[iNode]->SetValue(inputRunResults[index].in[iNode]);
            }
        }

        //Store results
        inputRunResults[index].result = outputNode->GetValue();
    }
}

void CircuitOptimizer::FillCustomTruthTable(TruthTable &results, size_t& numInputNodes)
{
    int size = pow(2, numInputNodes);
    for (int i = 0; i < size; i++)
    {
        results.push_back(RunOfGates());

        const std::string bin = DecimalToBinaryString(i, numInputNodes);
        for (char c : bin)
            results[i].in.push_back(c == '0' ? true : false);
    }
}
*/

std::string CircuitOptimizer::DecimalToBinaryString(int a, size_t reqLen)
{
    std::string binary = "";
    int mask = 1;
    for(int i = 0; i < reqLen; i++)
    {
        if((mask&a) >= 1)
            binary = "1"+binary;
        else
            binary = "0"+binary;
        mask<<=1;
    }

    return binary;
}

std::vector<Gate*> CircuitOptimizer::CuircuitFromBooleanAlgebra(BooleanExpression algebraicString, std::vector<Gate*>& defaultReturn)
{
    const int positionInc = 100;
    const QPoint startCuircuitLocation = defaultReturn[0]->GetPosition();
    QPoint cuircuitLocation = startCuircuitLocation;

    std::vector<Gate*> gates;

    while (algebraicString.letter.size() > 0)
    {
        for (size_t i = 0; i < algebraicString.letter.size(); i++)
        {

            //      letter & letter
            if ((algebraicString.letter.size() > i + 1) &&
                (isalpha(algebraicString.letter[i])) &&
                (isalpha(algebraicString.letter[i+1])))
            {
                //Add new gate
                gates.push_back(new GateAnd());
                size_t iNew = gates.size()-1;

                //Set new gates position
                cuircuitLocation.setY(cuircuitLocation.y() + positionInc);
                gates[iNew]->SetPosition(cuircuitLocation.x(), cuircuitLocation.y());

                //Check for not gates
                if (algebraicString.inverted[i] && algebraicString.inverted[i+1])
                {
                    iNew = LinkNotGateAsOutput(gates, iNew);
                }
                else if (algebraicString.inverted[i])
                {
                    LinkNotGateAsInput(gates, iNew, 0);
                }
                else if (algebraicString.inverted[i+1])
                {
                    LinkNotGateAsInput(gates, iNew, 1);
                }

                //Make adjuestments to algebraicString
                CutBooleanExpression(algebraicString,i,i+2);
                algebraicString.letter.insert(algebraicString.letter.begin()+i, std::to_string(iNew).c_str()[0]);
                algebraicString.inverted.insert(algebraicString.inverted.begin()+i, false);

                continue;
            }

            //      gate & gate
            if (algebraicString.letter.size() > i + 1 &&
                !isalpha(algebraicString.letter[i]) &&
                !isalpha(algebraicString.letter[i+1]))
            {
                gates.push_back(new GateAnd());

                //Link
                const size_t iNew = gates.size()-1;
                const size_t iFirst = IntFromChar(algebraicString.letter[i]);
                const size_t iSecond = IntFromChar(algebraicString.letter[i+1]);
                LinkThreeGates(gates, iNew, iFirst, iSecond);

                //Set new position
                cuircuitLocation.setX(cuircuitLocation.x() + positionInc);
                cuircuitLocation.setY(((cuircuitLocation.y() - startCuircuitLocation.y()) / 2) + startCuircuitLocation.y() - positionInc);
                gates[iNew]->SetPosition(cuircuitLocation.x(), cuircuitLocation.y());

                //Make adjuestments to algebraicString
                CutBooleanExpression(algebraicString,i,i+2);
                if (algebraicString.letter.size() > 0)
                {
                    algebraicString.letter.insert(algebraicString.letter.begin()+i, std::to_string(iNew).c_str()[0]);
                    algebraicString.inverted.insert(algebraicString.inverted.begin()+i, false);
                }

                continue;
            }

            //      gate & letter
            if ((algebraicString.letter.size() > i + 1) &&
                (!isalpha(algebraicString.letter[i])) &&
                (isalpha(algebraicString.letter[i+1])))
            {
                //Add new gate
                gates.push_back(new GateAnd());
                size_t iNew = gates.size()-1;
                const size_t iGateToLink = IntFromChar(algebraicString.letter[i]);

                //link algebraicString.letter[i] to new GateAnd()
                LinkTwoGates(gates, iGateToLink, iNew);

                //Set new gates position
                cuircuitLocation.setY(cuircuitLocation.y() + positionInc);
                gates[iNew]->SetPosition(cuircuitLocation.x(), cuircuitLocation.y());

                //Check for not gates in this case i will never be notted
                if (algebraicString.inverted[i+1])
                {
                    LinkNotGateAsInput(gates, iNew, 1);
                }

                //Make adjuestments to algebraicString
                CutBooleanExpression(algebraicString,i,i+2);
                algebraicString.letter.insert(algebraicString.letter.begin()+i, std::to_string(iNew).c_str()[0]);
                algebraicString.inverted.insert(algebraicString.inverted.begin()+i, false);

                continue;
            }

            //      letter | letter
            if (algebraicString.letter.size() > i + 1 && (i > -1) &&
                algebraicString.letter[i] == '+' &&
                isalpha(algebraicString.letter[i-1]) &&
                isalpha(algebraicString.letter[i+1]))
            {
                //Add new gate
                gates.push_back(new GateOr());
                size_t iNew = gates.size()-1;

                //Set new gates position
                gates[iNew]->SetPosition(cuircuitLocation.x(), cuircuitLocation.y());
                cuircuitLocation.setY(cuircuitLocation.y() + positionInc);

                //Check for not gates
                if (algebraicString.inverted[i-1] && algebraicString.inverted[i+1])
                {
                    iNew = LinkNotGateAsOutput(gates, iNew);
                }
                else if (algebraicString.inverted[i-1])
                {
                    LinkNotGateAsInput(gates, iNew, 0);
                }
                else if (algebraicString.inverted[i+1])
                {
                    LinkNotGateAsInput(gates, iNew, 1);
                }

                //Make adjuestments to algebraicString
                CutBooleanExpression(algebraicString,i-1,i+2);
                algebraicString.letter.insert(algebraicString.letter.begin()+i, std::to_string(iNew).c_str()[0]);
                algebraicString.inverted.insert(algebraicString.inverted.begin()+i, false);

                continue;
            }

            //      gate | gate
            if (algebraicString.letter.size() < i + 1 && (i > -1) &&
                algebraicString.letter[i] == '+' &&
                !isalpha(algebraicString.letter[i+1]) &&
                !isalpha(algebraicString.letter[i-1]))
            {
                gates.push_back(new GateOr());

                //Link
                const size_t iNew = gates.size()-1;
                const size_t iFirst = IntFromChar(algebraicString.letter[i-1]);
                const size_t iSecond = IntFromChar(algebraicString.letter[i+1]);
                LinkThreeGates(gates, iNew, iFirst, iSecond);

                //Set new position
                cuircuitLocation.setX(cuircuitLocation.x() + positionInc);
                cuircuitLocation.setY(((cuircuitLocation.y() - startCuircuitLocation.y()) / 2) + startCuircuitLocation.y() - positionInc);
                gates[iNew]->SetPosition(cuircuitLocation.x(), cuircuitLocation.y());

                //Make adjuestments to algebraicString
                CutBooleanExpression(algebraicString,i-1,i+2);
                if (algebraicString.letter.size() > 0)
                {
                    algebraicString.letter.insert(algebraicString.letter.begin()+i, std::to_string(iNew).c_str()[0]);
                    algebraicString.inverted.insert(algebraicString.inverted.begin()+i, false);
                }

                continue;
            }


            //      gate | letter
            if (algebraicString.letter.size() < i + 1 && (i > -1) &&
                algebraicString.letter[i] == '+' &&
                !isalpha(algebraicString.letter[i-1]) &&
                isalpha(algebraicString.letter[i+1]))
            {
                gates.push_back(new GateOr());
                const size_t iNew = gates.size()-1;
                const size_t iGateToLink = IntFromChar(algebraicString.letter[i-1]);

                //link algebraicString.letter[i-1] to new GateOr()
                LinkTwoGates(gates, iGateToLink, iNew);

                //Set new position
                gates[iNew]->SetPosition(cuircuitLocation.x(), cuircuitLocation.y());
                cuircuitLocation.setX(cuircuitLocation.x() + positionInc);
                cuircuitLocation.setY(cuircuitLocation.y() + positionInc);

                //Check for not gates in this case i will never be notted
                if (algebraicString.inverted[i+1])
                {
                    LinkNotGateAsInput(gates, iNew, 1);
                }

                //Make adjuestments to algebraicString
                CutBooleanExpression(algebraicString,i-1,i+2);
                if (algebraicString.letter.size() > 0)
                {
                    algebraicString.letter.insert(algebraicString.letter.begin()+i, std::to_string(iNew).c_str()[0]);
                    algebraicString.inverted.insert(algebraicString.inverted.begin()+i, false);
                }
            }
        }
    }

    if (gates.size() > 1)
        return gates;

    //todo
    return defaultReturn;
}

int CircuitOptimizer::IntFromChar(char c)
{
    std::string s;
    s.push_back(c);
    return stoi(s);
}

void CircuitOptimizer::CutBooleanExpression(CircuitOptimizer::BooleanExpression &expression, size_t iStart, size_t iEnd)
{
    expression.letter.erase(expression.letter.begin() + iStart, expression.letter.begin() + iEnd);
    expression.inverted.erase(expression.inverted.begin() + iStart, expression.inverted.begin() + iEnd);
}

void CircuitOptimizer::LinkNotGateAsInput(std::vector<Gate*> &gates, size_t iGateToLinkTo, size_t iInputNode)
{
    gates.push_back(new GateNot());

    std::vector<Node*> outNodes;
    gates[gates.size() - 1]->GetDisconnectedOutputNodes(outNodes);

    std::vector<Node*> inputNodes;
    gates[iGateToLinkTo]->GetDisconnectedInputNodes(inputNodes);

    outNodes[0]->LinkNode(inputNodes[iInputNode]);
    inputNodes[iInputNode]->LinkNode(outNodes[0]);
}

size_t CircuitOptimizer::LinkNotGateAsOutput(std::vector<Gate*> &gates, size_t iGateToLinkTo)
{
    gates.push_back(new GateNot());
    const size_t notIndex = gates.size() - 1;

    std::vector<Node*> inputNodes;
    gates[notIndex]->GetDisconnectedInputNodes(inputNodes);

    std::vector<Node*> outputNodes;
    gates[iGateToLinkTo]->GetDisconnectedOutputNodes(outputNodes);

    outputNodes[0]->LinkNode(inputNodes[0]);
    inputNodes[0]->LinkNode(outputNodes[0]);

    return notIndex;
}

//Links iFirst's & iSecond's output nodes to input nodes of iLinkGate
bool CircuitOptimizer::LinkThreeGates(std::vector<Gate *> &gates, size_t iLinkGate, size_t iFirst, size_t iSecond)
{
    std::vector<Node*> inputNodes;
    gates[iLinkGate]->GetDisconnectedInputNodes(inputNodes);

    std::vector<Node*> outNodes;
    gates[iFirst]->GetDisconnectedOutputNodes(outNodes);
    gates[iSecond]->GetDisconnectedOutputNodes(outNodes);

    const bool linkAA = outNodes[0]->LinkNode(inputNodes[0]);
    const bool linkAB = inputNodes[0]->LinkNode(outNodes[0]);

    const bool linkBA = outNodes[1]->LinkNode(inputNodes[1]);
    const bool linkBB = inputNodes[1]->LinkNode(outNodes[1]);

    return (linkAA & linkAB & linkBA & linkBB);
}

//Links iFirst's output node into iSecond's first free input node
bool CircuitOptimizer::LinkTwoGates(std::vector<Gate*> &gates, size_t iFirst, size_t iSecond)
{
    std::vector<Node*> outNodes;
    gates[iFirst]->GetDisconnectedOutputNodes(outNodes);

    std::vector<Node*> inputNodes;
    gates[iSecond]->GetDisconnectedInputNodes(inputNodes);

    const bool linkA = outNodes[0]->LinkNode(inputNodes[0]);
    const bool linkB = inputNodes[0]->LinkNode(outNodes[0]);

    return (linkA & linkB);
}


//-------------------------------------------------------------------------------------------------------------
// Quine–McCluskey Algorithm
// =========================
//-------------------------------------------------------------------------------------------------------------
// Description: Application to simplify boolean functions with Quine-McCluskey algorithm
// Date: 05/16/2012
// Author: Stefan Moebius (mail@stefanmoebius.de)
// Licence: Can be used freely (Public Domain)

//Count all set bits of the integer number
// ~ Taken from book "Hackers Delight"
int CircuitOptimizer::PopCount(unsigned x)
{
    x = x - ((x >> 1) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x + (x >> 4)) & 0x0F0F0F0F;
    x = x + (x >> 8);
    x = x + (x >> 16);
    return x & 0x0000003F;
}

//Calculate hamming weight/distance of two integer numbers
int CircuitOptimizer::HammingWeight(int v1, int v2)
{
    return PopCount(v1 ^ v2);
}

//Output upper part of term in console
void CircuitOptimizer::UpperTerm(int bitfield, int mask, int num, BooleanExpression& returnExpression)
{
    if (mask)
    {
        int z;
        for ( z = 0; z < num; z++)
        {
            if (mask & (1 << z))
            {
                returnExpression.inverted.push_back((bitfield & (1 << z)));
            }
        }
    }
}

//Output lower part of term in console
void CircuitOptimizer::LowerTerm(int mask, int num, BooleanExpression& returnExpression)
{
    if (mask)
    {
        int z;
        for (z = 0; z < num; z++)
        {
            if (mask & (1 << z))
            {
                returnExpression.letter.push_back(("%c", 'z' - (num - 1) + z));
            }
        }
    }
}

//Determines whether "value" contains "part"
int CircuitOptimizer::Contains(int value, int mask, int part, int partmask)
{
    if ((value & partmask) == (part & partmask)) {
        if ((mask & partmask) ==  partmask)
            return TRUE;
    }
    return FALSE;
}

bool CircuitOptimizer::OptimizedBooleanAlgebraFromTruthTable(size_t numInputs, CircuitOptimizer::TruthTable truthTable, BooleanExpression& returnExpression)
{
    int pos = 0;
    int cur = 0;
    int reduction = 0; //reduction step
    int maderedction = FALSE;
    int prim_count = 0;
    int term = 0;
    int termmask = 0;
    int found = 0;
    int x = 0;
    int y = 0;
    int z = 0;
    int count = 0;
    int lastprim = 0;
    int res = 0; // actual result

    // Fill all arrays with default values
    for (x = 0; x < MAX; x++)
    {
        primmask[x] = 0;
        prim[x] = 0;
        wprim[x] = FALSE;
        nwprim[x] = FALSE;
        result[x] = FALSE;
        nwprim[x] = TRUE;
        for (y = 0; y < MAX; y++)
        {
            mask[x][y] = 0;
            minterm[x][y] = 0;
            used[x][y] = FALSE;
        }
    }

    //To many vars
    if (numInputs > MAXVARS)
        return 0;

    //Not enough vars
    if (numInputs < 1)
        return 0;


    pos = (1 << numInputs);
    cur = 0;

    //Iterate truth table results
    for ( x=0; x < pos; x++)
    {
        if (truthTable[x].result)
        {
            mask[cur][0] = ((1 << numInputs)- 1);
            minterm[cur][0] = x;
            cur++;
            result[x] = 1;
        }
    }

    for (reduction = 0; reduction < MAX; reduction++)
    {
        cur = 0;
        maderedction = FALSE;
        for (y=0; y < MAX; y++) {
            for (x=0; x < MAX; x++) {
                if ((mask[x][reduction]) && (mask[y][reduction]))
                {
                    // Do not allow complete removal (problem if all terms are 1)
                    if (PopCount(mask[x][reduction]) > 1)
                    {
                        // Simplification only possible if 1 bit differs
                        if ((HammingWeight(minterm[x][reduction] & mask[x][reduction], minterm[y][reduction] & mask[y][reduction]) == 1) && (mask[x][reduction] == mask[y][reduction]))
                        {
                            // could be mintern x or y
                            term = minterm[x][reduction];
                            //e.g.:
                            //1110
                            //1111
                            //Should result in mask of 1110
                            termmask = mask[x][reduction]  ^ (minterm[x][reduction] ^ minterm[y][reduction]);
                            term  &= termmask;

                            found = FALSE;
                            for ( z=0; z<cur; z++)
                            {
                                if ((minterm[z][reduction+1] == term) && (mask[z][reduction+1] == termmask) )
                                {
                                    found = TRUE;
                                }
                            }

                            if (found == FALSE)
                            {
                                minterm[cur][reduction+1] = term;
                                mask[cur][reduction+1] = termmask;
                                cur++;
                            }
                            used[x][reduction] = TRUE;
                            used[y][reduction] = TRUE;
                            maderedction = TRUE;
                        }
                    }
                }
            }
        }
        if (maderedction == FALSE)
            break; //exit loop early (speed optimisation)
    }

    prim_count = 0;
    for ( reduction = 0 ; reduction < MAX; reduction++)
    {
        for ( x=0 ;x < MAX; x++)
        {
            //Determine all not used minterms
            if ((used[x][reduction] == FALSE) && (mask[x][reduction]) )
            {
                //Check if the same prime implicant is already in the list
                found = FALSE;
                for ( z=0; z < prim_count; z++)
                {
                    if (((prim[z] & primmask[z]) == (minterm[x][reduction] & mask[x][reduction])) &&  (primmask[z] == mask[x][reduction]) )
                        found = TRUE;
                }
                if (found == FALSE)
                {
                    primmask[prim_count] = mask[x][reduction];
                    prim[prim_count] = minterm[x][reduction];
                    prim_count++;
                }
            }
        }
    }

    //find essential and not essential prime implicants
    //all prime implicants are set to "not essential" so far
    //for all minterms
    for (y=0; y < pos; y++)
    {
        count = 0;
        lastprim = 0;
        if (mask[y][0])
        {
            //for all prime implicants
            for (x=0; x < prim_count; x++ )
            {
                // Check if the minterm contains prime implicant
                if (primmask[x])
                {
                    if (Contains(minterm[y][0], mask[y][0], prim[x], primmask[x]))
                    {
                        count++;
                        lastprim = x;
                    }
                }
            }

            // If count = 1 then it is a essential prime implicant
            if (count == 1)
            {
                wprim[lastprim] = TRUE;
            }
        }
    }

    // successively testing if it is possible to remove prime implicants from the rest matrix
    for ( z=0; z < prim_count; z++)
    {
        if (primmask[z] )
        {
            if ((wprim[z] == FALSE))
            {
                // mark as "not essential"
                nwprim[z] = FALSE;

                // for all possibilities
                for ( y=0; y < pos; y++)
                {
                    res = 0;
                    for ( x=0; x < prim_count; x++)
                    {
                        //essential prime implicant or marked as required
                        if ( (wprim[x] == TRUE) || (nwprim[x] == TRUE))
                        {
                            //All bits must be 1
                            if ((y & primmask[x]) == (prim[x] & primmask[x]))
                            {
                                res = 1;
                                break;
                            }
                        }
                    }

                    if (res == result[y])
                    {
                        // compare calculated result with input value
                        // prime implicant not required
                    }
                    else
                    {
                        //prime implicant required
                        nwprim[z] = TRUE;
                    }
                }
            }
        }
    }

    // Output of essential and required prime implicants
    count = 0;
    for ( x = 0 ; x < prim_count; x++)
    {
        if (wprim[x] == TRUE)
        {
            if (count > 0)
            {
                returnExpression.letter.push_back(' ');
                returnExpression.letter.push_back('.');
                returnExpression.letter.push_back(' ');
                returnExpression.inverted.push_back(0);
                returnExpression.inverted.push_back(0);
                returnExpression.inverted.push_back(0);
            }

            UpperTerm(prim[x], primmask[x], numInputs, returnExpression);
            count++;
        }
        else if ((wprim[x] == FALSE) && (nwprim[x] == TRUE))
        {
            if (count > 0)
            {
                returnExpression.letter.push_back(' ');
                returnExpression.letter.push_back('.');
                returnExpression.letter.push_back(' ');
                returnExpression.inverted.push_back(0);
                returnExpression.inverted.push_back(0);
                returnExpression.inverted.push_back(0);
            }

            UpperTerm(prim[x], primmask[x], numInputs, returnExpression);
            count++;
        }
    }

    count = 0;
    for ( x = 0 ; x < prim_count; x++)
    {
        if (wprim[x] == TRUE)
        {
            if (count > 0)
            {
                returnExpression.letter.push_back('+');
                returnExpression.inverted.push_back(0);
            }

            LowerTerm(primmask[x], numInputs, returnExpression);
            count++;
        }

        else if ((wprim[x] == FALSE) && (nwprim[x] == TRUE))
        {
            if (count > 0)
            {
                returnExpression.letter.push_back('+');
                returnExpression.inverted.push_back(0);
            }

            LowerTerm(primmask[x], numInputs, returnExpression);
            count++;
        }
    }

    return 1;
}




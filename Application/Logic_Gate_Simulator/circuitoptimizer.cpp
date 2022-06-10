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

std::vector<Gate*> CircuitOptimizer::Optimize(std::vector<Gate*>& gates, bool nandOnly)
{
    size_t numInputNodes = 0;
    TruthTable tt;
    if ( !TruthTableFromCircuit( gates, tt, numInputNodes ) )
        return gates;

    BooleanExpression expression;
    if ( !OptimizedBooleanAlgebraFromTruthTable( numInputNodes, tt, expression ) )
        return gates;

    if (nandOnly)
    {
        return NandCuircuitFromBooleanAlgebra(expression, gates);
    }
    else
    {
        return CuircuitFromBooleanAlgebra(expression, gates);
    }
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
            inputNodes[iNode]->setValue(bIn);
        }

        table[i].result = outputNodes[0]->value();
    }

    return true;
}

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
    const int positionInc = 110;
    const QPoint startGateLocation = defaultReturn[0]->position();

    std::vector<Gate*> gates;

    while (algebraicString.letter.size() > 0)
    {

        //      letter & letter
        for (size_t i = 0; i < algebraicString.letter.size(); i++)
        {
            if ((algebraicString.letter.size() > i + 1) &&
                (isalpha(algebraicString.letter[i])) &&
                (isalpha(algebraicString.letter[i+1])))
            {
                //Add new gate
                gates.push_back(new GateAnd());
                size_t iNew = gates.size()-1;

                //Set new gates position
                QPoint pos;
                if (gates.size() == 1)
                {
                    pos = startGateLocation;
                }
                else
                {
                    const QPoint previousGatePos = gates[gates.size() - 2]->position();
                    pos = QPoint(previousGatePos.x(), previousGatePos.y() + positionInc);
                }
                gates[iNew]->setPosition(pos.x(), pos.y());

                //Check for not gates
                if (algebraicString.inverted[i] && algebraicString.inverted[i+1])
                {
                    iNew = LinkNotGateAsOutput(gates, iNew);
                }
                else if (algebraicString.inverted[i] || algebraicString.inverted[i+1])
                {
                    LinkNotGateAsInput(gates, iNew);
                }

                //Make adjuestments to algebraicString
                CutBooleanExpression(algebraicString,i,i+2);
                algebraicString.letter.insert(algebraicString.letter.begin()+i, std::to_string(iNew).c_str()[0]);
                algebraicString.inverted.insert(algebraicString.inverted.begin()+i, false);
            }
        }

        //      gate & gate
        for (size_t i = 0; i < algebraicString.letter.size(); i++)
        {
            if (algebraicString.letter.size() > i + 1 &&
                !isalpha(algebraicString.letter[i]) && algebraicString.letter[i] != '+' &&
                !isalpha(algebraicString.letter[i+1]) && algebraicString.letter[i+1] != '+')
            {
                gates.push_back(new GateAnd());

                //Link
                const size_t iNew = gates.size()-1;
                const size_t iFirst = IntFromChar(algebraicString.letter[i]);
                const size_t iSecond = IntFromChar(algebraicString.letter[i+1]);
                LinkThreeGates(gates, iNew, iFirst, iSecond);

                //Set new position
                const QPoint firstPoint = gates[iFirst]->position();
                const QPoint secondPoint = gates[iSecond]->position();
                gates[iNew]->setPosition(secondPoint.x() + positionInc, (secondPoint.y() - firstPoint.y())/2 + firstPoint.y());

                //Make adjuestments to algebraicString
                CutBooleanExpression(algebraicString,i,i+2);
                if (algebraicString.letter.size() > 0)
                {
                    algebraicString.letter.insert(algebraicString.letter.begin()+i, std::to_string(iNew).c_str()[0]);
                    algebraicString.inverted.insert(algebraicString.inverted.begin()+i, false);
                }
            }
        }

        //      gate & letter
        for (size_t i = 0; i < algebraicString.letter.size(); i++)
        {
            if ((algebraicString.letter.size() > i + 1) &&
                (!isalpha(algebraicString.letter[i])) && algebraicString.letter[i] != '+' &&
                (isalpha(algebraicString.letter[i+1])))
            {
                //Add new gate
                gates.push_back(new GateAnd());
                size_t iNew = gates.size()-1;
                const size_t iGateToLink = IntFromChar(algebraicString.letter[i]);

                //link algebraicString.letter[i] to new GateAnd()
                LinkTwoGates(gates, iGateToLink, iNew);

                //Set new gates position
                const QPoint firstGatePos = gates[iGateToLink]->position();
                gates[iNew]->setPosition(firstGatePos.x(), firstGatePos.y() + positionInc);

                //Check for not gates in this case 'i' will never be notted
                if (algebraicString.inverted[i+1])
                {
                    LinkNotGateAsInput(gates, iNew);
                }

                //Make adjuestments to algebraicString
                CutBooleanExpression(algebraicString,i,i+2);
                algebraicString.letter.insert(algebraicString.letter.begin()+i, std::to_string(iNew).c_str()[0]);
                algebraicString.inverted.insert(algebraicString.inverted.begin()+i, false);
            }
        }

        //      letter | letter
        for (size_t i = 0; i < algebraicString.letter.size(); i++)
        {
            if (algebraicString.letter.size() > i + 2 &&
                isalpha(algebraicString.letter[i]) &&
                algebraicString.letter[i+1] == '+' &&
                isalpha(algebraicString.letter[i+2]))
            {
                //Add new gate
                gates.push_back(new GateOr());
                size_t iNew = gates.size()-1;

                //Set new gates position
                QPoint pos;
                if (gates.size() == 1)
                {
                    pos = startGateLocation;
                }
                else
                {
                    const QPoint previousGatePos = gates[gates.size() - 2]->position();
                    pos = QPoint(previousGatePos.x(), previousGatePos.y() + positionInc);
                }
                gates[iNew]->setPosition(pos.x(), pos.y());

                //Check for not gates
                if (algebraicString.inverted[i] && algebraicString.inverted[i+2])
                {
                    iNew = LinkNotGateAsOutput(gates, iNew);
                }
                else if (algebraicString.inverted[i] || algebraicString.inverted[i+2])
                {
                    LinkNotGateAsInput(gates, iNew);
                }

                //Make adjuestments to algebraicString
                CutBooleanExpression(algebraicString,i,i+3);
                algebraicString.letter.insert(algebraicString.letter.begin()+i, std::to_string(iNew).c_str()[0]);
                algebraicString.inverted.insert(algebraicString.inverted.begin()+i, false);
            }
        }

        //      gate | gate
        for (size_t i = 0; i < algebraicString.letter.size(); i++)
        {
            if (algebraicString.letter.size() >= i + 2 &&
                !isalpha(algebraicString.letter[i]) && algebraicString.letter[i] != '+' &&
                algebraicString.letter[i+1] == '+' &&
                !isalpha(algebraicString.letter[i+2]) && algebraicString.letter[i+2] != '+')
            {
                gates.push_back(new GateOr());

                //Link
                const size_t iNew = gates.size()-1;
                const size_t iFirst = IntFromChar(algebraicString.letter[i]);
                const size_t iSecond = IntFromChar(algebraicString.letter[i+2]);
                LinkThreeGates(gates, iNew, iFirst, iSecond);

                //Set new position
                const QPoint firstPoint = gates[iFirst]->position();
                const QPoint secondPoint = gates[iSecond]->position();
                gates[iNew]->setPosition(secondPoint.x() + positionInc, (secondPoint.y() - firstPoint.y())/2 + firstPoint.y());

                //Make adjuestments to algebraicString
                CutBooleanExpression(algebraicString,i,i+3);
                if (algebraicString.letter.size() > 0)
                {
                    algebraicString.letter.insert(algebraicString.letter.begin()+i, std::to_string(iNew).c_str()[0]);
                    algebraicString.inverted.insert(algebraicString.inverted.begin()+i, false);
                }
            }
        }

        //      gate | letter
        for (size_t i = 0; i < algebraicString.letter.size(); i++)
        {
            if (algebraicString.letter.size() >= i + 2 &&
                !isalpha(algebraicString.letter[i]) && algebraicString.letter[i] != '+' &&
                algebraicString.letter[i+1] == '+' &&
                isalpha(algebraicString.letter[i+2]))
            {
                gates.push_back(new GateOr());
                const size_t iNew = gates.size()-1;
                const size_t iGateToLink = IntFromChar(algebraicString.letter[i]);

                //link algebraicString.letter[i-1] to new GateOr()
                LinkTwoGates(gates, iGateToLink, iNew);

                //Set new gates position
                const QPoint firstGatePos = gates[iGateToLink]->position();
                gates[iNew]->setPosition(firstGatePos.x(), firstGatePos.y() + positionInc);

                //Check for not gates in this case i will never be notted
                if (algebraicString.inverted[i+1])
                {
                    LinkNotGateAsInput(gates, iNew);
                }

                //Make adjuestments to algebraicString
                CutBooleanExpression(algebraicString,i,i+3);
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

    return defaultReturn;
}

std::vector<Gate *> CircuitOptimizer::NandCuircuitFromBooleanAlgebra(CircuitOptimizer::BooleanExpression algebraicString, std::vector<Gate *> &defaultReturn)
{
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

void CircuitOptimizer::LinkNotGateAsInput(std::vector<Gate*> &gates, size_t iGateToLinkTo)
{
    gates.push_back(new GateNot());
    const QPoint previousGatePos = gates[gates.size() - 2]->position();
    gates[gates.size() - 1]->setPosition(previousGatePos.x()-100, previousGatePos.y());

    std::vector<Node*> outNodes;
    gates[gates.size() - 1]->GetDisconnectedOutputNodes(outNodes);

    std::vector<Node*> inputNodes;
    gates[iGateToLinkTo]->GetDisconnectedInputNodes(inputNodes);

    inputNodes[0]->LinkNode(outNodes[0]);
    outNodes[0]->LinkNode(inputNodes[0]);
}

size_t CircuitOptimizer::LinkNotGateAsOutput(std::vector<Gate*> &gates, size_t iGateToLinkTo)
{
    //If it's a gate type that has an opposite type (ie. And & Nand) switch it with its opposing type
    //Otherwise just add a not gate onto the end of the gate
    switch (gates[iGateToLinkTo]->GetType())
    {
        case GateType::GATE_AND:
            SwitchGates(gates, new GateNand(), iGateToLinkTo);
            return iGateToLinkTo;

        case GateType::GATE_OR:
            SwitchGates(gates, new GateNor(), iGateToLinkTo);
            return iGateToLinkTo;

        case GateType::GATE_EOR:
            SwitchGates(gates, new GateXor(), iGateToLinkTo);
            return iGateToLinkTo;

        default:
            gates.push_back(new GateNot());
            const size_t iNewNot = gates.size() - 1;

            const QPoint previousGatePos = gates[gates.size() - 2]->position();
            gates[iNewNot]->setPosition(previousGatePos.x() + 100, previousGatePos.y());

            std::vector<Node*> inputNodes;
            gates[iNewNot]->GetDisconnectedInputNodes(inputNodes);

            std::vector<Node*> outputNodes;
            gates[iGateToLinkTo]->GetDisconnectedOutputNodes(outputNodes);

            outputNodes[0]->LinkNode(inputNodes[0]);
            inputNodes[0]->LinkNode(outputNodes[0]);

            return iNewNot;
            break;
    }
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

void CircuitOptimizer::SwitchGates(std::vector<Gate *> &gates, Gate *gateToSwitch, size_t indexToSwitch)
{
    //Don't need to worry about nodes, function only called for gates not connected to anything

    delete gates[indexToSwitch];
    gates[indexToSwitch] = gateToSwitch;
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
            /*if (count > 0)
            {
                returnExpression.letter.push_back(' ');
                returnExpression.letter.push_back('.');
                returnExpression.letter.push_back(' ');
                returnExpression.inverted.push_back(0);
                returnExpression.inverted.push_back(0);
                returnExpression.inverted.push_back(0);
            }*/

            UpperTerm(prim[x], primmask[x], numInputs, returnExpression);
            count++;
        }
        else if ((wprim[x] == FALSE) && (nwprim[x] == TRUE))
        {
            /*if (count > 0)
            {
                returnExpression.letter.push_back(' ');
                returnExpression.letter.push_back('.');
                returnExpression.letter.push_back(' ');
                returnExpression.inverted.push_back(0);
                returnExpression.inverted.push_back(0);
                returnExpression.inverted.push_back(0);
            }*/

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




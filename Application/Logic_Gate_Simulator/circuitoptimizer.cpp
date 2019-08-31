#include "circuitoptimizer.h"
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
    int numInputNodes = 0;
    TruthTable tt;
    if ( !TruthTableFromCircuit(gates, tt, numInputNodes) )
        return gates;

    BooleanExpression expression;
    if ( !OptimizedBooleanAlgebraFromTruthTable( numInputNodes, tt, expression ) )
        return gates;

    return CuircuitFromBooleanAlgebra(expression);
}

bool CircuitOptimizer::TruthTableFromCircuit(std::vector<Gate*>& gates, TruthTable& table, size_t numInputNodes)
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
    if (numInputNodes < 2 || numInputNodes == 0)
        return false;

    FillCustomTruthTable(table, numInputNodes);

    GateRun(table, inputNodes, outputNodes, numInputNodes);

    return true;
}

void CircuitOptimizer::GateRun(std::vector<InputRunResults>& inputRunResults, std::vector<Node*>& inputNodes, std::vector<Node*>& outputNodes, const size_t numInputNodes)
{
    for (InputRunResults results : inputRunResults)
    {
        //Run it twice just to be sure. can probably remove this after
        for (int x = 0; x < 2; x++)
        {
            for (size_t x = 0; x < numInputNodes; x++)
            {
                inputNodes[x]->SetValue(results.in[x]);
            }
        }

        //Store results
        for (Node* n : outputNodes)
        {
            results.result.push_back(n->GetValue());
        }
    }
}

void CircuitOptimizer::FillCustomTruthTable(TruthTable &results, size_t& numInputNodes)
{
    int n = 3;
    int size = pow(2, numInputNodes);
    for (int i = 0; i < size; i++)
    {
        results.push_back(InputRunResults());

        std::string bin = DecimalToBinaryString(i);
        while (bin.length() < n)
            bin = "0" + bin;

        std::vector<bool> boolArray;
        for (char c : bin)
        {
            boolArray.push_back(c == '0' ? true : false);
        }

        results[results.size()-1].in = boolArray;
    }

}

std::string CircuitOptimizer::DecimalToBinaryString(int a)
{
    std::string binary = "";
    int mask = 1;
    for(int i = 0; i < 31; i++)
    {
        if((mask&a) >= 1)
            binary = "1"+binary;
        else
            binary = "0"+binary;
        mask<<=1;
    }

    return binary;
}

std::vector<Gate*> CircuitOptimizer::CuircuitFromBooleanAlgebra(BooleanExpression algebraicString)
{
    //todo
    return std::vector<Gate*>();
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

bool CircuitOptimizer::OptimizedBooleanAlgebraFromTruthTable(int numInputs, CircuitOptimizer::TruthTable truthTable, BooleanExpression& returnExpression)
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
        if (truthTable[x].result[0])
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
    //all alle prime implicants are set to "not essential" so far
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
                returnExpression.letter.push_back(' ');

            UpperTerm(prim[x], primmask[x], numInputs, returnExpression);
            count++;
        }
        else if ((wprim[x] == FALSE) && (nwprim[x] == TRUE))
        {
            if (count > 0)
                returnExpression.letter.push_back(' ');

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
                returnExpression.letter.push_back('+');

            LowerTerm(primmask[x], numInputs, returnExpression);
            count++;
        }

        else if ((wprim[x] == FALSE) && (nwprim[x] == TRUE))
        {
            if (count > 0)
                returnExpression.letter.push_back('+');

            LowerTerm(primmask[x], numInputs, returnExpression);
            count++;
        }
    }

    return 1;
}




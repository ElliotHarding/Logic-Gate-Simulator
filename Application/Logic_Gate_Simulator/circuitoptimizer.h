#ifndef CIRCUITOPTIMIZER_H
#define CIRCUITOPTIMIZER_H

#include "gate.h"

/*
    Things to considor when optimising :

    1. Correctness/Simplicity
    Does it implement the correct function? How hard will it be to verify that the
    circuit really works? How hard will it be to test the chip?

    2. Area
    How much space does it take to build this circuit. Is it small enough? This
    depends on the implementation technology (board / std cell / custom)

    3. Speed
    How fast will the circuit run. Is the maximum clock rate fast enough?

    4. Design Time
    How long have you been working on it. Is it time to call it done?

    5. Power


    Option ~ Convert cuircuit to boolean algebra, do optimisation, and then reconvert into cuircuit

//optimization algorithms:
    https://en.wikipedia.org/wiki/Quine%E2%80%93McCluskey_algorithm
    https://sourceforge.net/projects/qmcs/

//Logic gates to boolean algebra
*/

#define TRUE 1
#define FALSE 0
#define MAXVARS 7
#define MAX 2048

class CircuitOptimizer
{
public:
    CircuitOptimizer();

    static std::vector<Gate*> Optimize(std::vector<Gate*>& gates, bool nandOnly);

private:

    //
    // -- STRUCTS & TYPEDEFS --
    //

    struct BooleanExpression
    {
        std::vector<char> letter;
        std::vector<bool> inverted;
    };

    struct RunOfGates
    {
        std::vector<bool> in;
        bool result;
    };
    typedef std::vector<RunOfGates> TruthTable;

private:

    //
    // -- Members --
    //

    static int minterm[MAX][MAX];
    static int mask[MAX][MAX];		// mask of minterm
    static int used[MAX][MAX];		// minterm used
    static int result[MAX];		// results
    static int primmask[MAX];		// mask for prime implicants
    static int prim[MAX];			// prime implicant
    static int wprim[MAX];			// essential prime implicant (TRUE/FALSE)
    static int nwprim[MAX];		// needed not essential prime implicant

    //
    // -- Functions --
    //

    static bool TruthTableFromCircuit(std::vector<Gate*>& gates, TruthTable& table, size_t& numInputNodes);

    static std::string DecimalToBinaryString(int a, size_t reqLen);

    /*
    static void FillCustomTruthTable(TruthTable& results, size_t& numInputNodes);
    static void GateRun(TruthTable& inputRunResults,
                 std::vector<Node*>& inputNodes, Node*& outputNode,
                 const size_t numInputNodes, std::vector<Gate*>& gates);
                 */

    static std::vector<Gate*> CuircuitFromBooleanAlgebra(BooleanExpression algebraicString, std::vector<Gate*>& defaultReturn);

    static std::vector<Gate*> NandCuircuitFromBooleanAlgebra(BooleanExpression algebraicString, std::vector<Gate*>& defaultReturn);

    static int IntFromChar(char c);

    static void CutBooleanExpression(BooleanExpression& expression, size_t iStart, size_t iEnd);

    static void LinkNotGateAsInput(std::vector<Gate*> &gates, size_t iGateToLinkTo);
    static size_t LinkNotGateAsOutput(std::vector<Gate*> &gates, size_t iGateToLinkTo);

    static bool LinkThreeGates(std::vector<Gate *> &gates, size_t iLinkGate, size_t iFirst, size_t iSecond);
    static bool LinkTwoGates(std::vector<Gate *> &gates, size_t iFirst, size_t iSecond);

    static bool OptimizedBooleanAlgebraFromTruthTable(size_t numInputs, CircuitOptimizer::TruthTable truthTable, BooleanExpression& result);

    static int PopCount(unsigned x);

    static int HammingWeight(int v1, int v2);

    static void UpperTerm(int bitfield, int mask, int num, BooleanExpression& returnExpression);

    static void LowerTerm(int mask, int num, BooleanExpression& returnExpression);

    static int Contains(int value, int mask, int part, int partmask);
};

#endif // CIRCUITOPTIMIZER_H

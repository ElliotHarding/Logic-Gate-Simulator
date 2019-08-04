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

class CircuitOptimizer
{
public:
    CircuitOptimizer();

    std::vector<Gate*> Optimize(std::vector<Gate*>& gates, bool failed);

private:

    struct InputRunResults
    {
        std::vector<bool> in;
        std::vector<bool> result;
    };

    std::string OptimizeBooleanAlgebra(const std::string& initalString);
    std::string BooleanAlgebraFromCircuit(std::vector<Gate*>& gates);
    std::vector<Gate*> CuircuitFromBooleanAlgebra(std::string algebraicString);

    void FillCustomTruthTable(std::vector<InputRunResults>& results, const size_t& numInputNodes);

private:
    std::string DecimalToBinaryString(int a);
};

#endif // CIRCUITOPTIMIZER_H
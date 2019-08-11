#include "circuitoptimizer.h"
#include <cmath>

CircuitOptimizer::CircuitOptimizer()
{

}

std::vector<Gate*> CircuitOptimizer::Optimize(std::vector<Gate*>& gates)
{
    return OptimizedCuircuitFromTruthTable(
                TruthTableFromCircuit(gates)
                );
}

CircuitOptimizer::TruthTable CircuitOptimizer::TruthTableFromCircuit(std::vector<Gate*>& gates)
{
    std::vector<CircuitOptimizer::InputRunResults> inputRunResults;

    //Need to get all input nodes that are not connected & all output nodes that are not connected
    std::vector<Node*> inputNodes;
    std::vector<Node*> outputNodes;
    for (Gate* g : gates)
    {
        g->GetDisconnectedInputNodes(inputNodes);
        g->GetDisconnectedOutputNodes(outputNodes);
    }

    //Check what happens when input values are changed
    const size_t numInputNodes = inputNodes.size();

    //Nothing to optimise
    if (numInputNodes < 2 || numInputNodes == 0)
        return inputRunResults;

    FillCustomTruthTable(inputRunResults, numInputNodes);

    GateRun(inputRunResults, inputNodes, outputNodes, numInputNodes);

    return inputRunResults;
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

void CircuitOptimizer::FillCustomTruthTable(TruthTable &results, const size_t& numInputNodes)
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

        results[results.size()].in = boolArray;
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

std::vector<Gate*> CircuitOptimizer::OptimizedCuircuitFromTruthTable(CircuitOptimizer::TruthTable tt)
{

}

std::string CircuitOptimizer::BooleanAlgebraFromTruthTable(TruthTable& results)
{

}

std::string CircuitOptimizer::OptimizeBooleanAlgebra(const std::string& initalString)
{

}

std::vector<Gate*> CircuitOptimizer::CuircuitFromBooleanAlgebra(std::string algebraicString)
{

}




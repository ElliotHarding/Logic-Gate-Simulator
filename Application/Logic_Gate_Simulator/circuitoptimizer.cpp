#include "circuitoptimizer.h"

CircuitOptimizer::CircuitOptimizer()
{

}

std::vector<Gate*> CircuitOptimizer::Optimize(std::vector<Gate*>& gates, bool failed)
{
    return CuircuitFromBooleanAlgebra(
                OptimizeBooleanAlgebra(
                            BooleanAlgebraFromCircuit(gates)
                    )
                );
}

std::string CircuitOptimizer::OptimizeBooleanAlgebra(const std::string& initalString)
{

}

std::string CircuitOptimizer::BooleanAlgebraFromCircuit(std::vector<Gate*>& gates)
{
    //Need to get all input nodes that are not connected & all output nodes that are not connected
    std::vector<Node*> inputNodes;
    std::vector<Node*> outputNodes;
    for (Gate* g : gates)
    {
        g->GetDisconnectedInputNodes(inputNodes);
        g->GetDisconnectedOutputNodes(outputNodes);
    }

    //Nothing to optimise
    if (inputNodes.size() < 2 || outputNodes.size() == 0)
        return "";

    //Check what happens when input values are changed
    const size_t numInputNodes = inputNodes.size();
    std::vector<InputRunResults> inputRunResults;





    for (size_t x = 0; x < numInputNodes; x++)
    {
        inputNodes[x]->SetValue(false);
    }

    for (size_t x = 0; x < numInputNodes; x++)
    {
        inputNodes[x]->SetValue(false);
    }

    for (size_t x = 0; x < numInputNodes; x++)
    {
        in.push_back(true);
    }

    GateRun(in, out, inputNodes, outputNodes, numInputNodes, false);


}

void GateRun(std::vector<bool>& in, std::vector<bool>& out, std::vector<Node*>& inputNodes, std::vector<Node*>& outputNodes, const size_t numInputNodes, bool bSetOneByOne)
{
    for (size_t run = 0; run < numInputNodes; run++)
    {
        for (size_t x = 0; x < numInputNodes; x++)
        {
            inputNodes[x]->SetValue(in[x]);
        }
        in[run] = bSetOneByOne;

        //Do execution


        //Store results

    }

    for (size_t x = 0; x < numInputNodes; x++)
    {
        inputNodes[x]->SetValue(in[x]);
    }
}

std::vector<Gate*> CircuitOptimizer::CuircuitFromBooleanAlgebra(std::string algebraicString)
{

}

void CircuitOptimizer::FillCustomTruthTable(std::vector<CircuitOptimizer::InputRunResults> &results, const size_t& numInputNodes)
{
    int n = 3;
    int size = 2^numInputNodes;
    for (int i = 0; i < size; i++)
    {
        results.push_back(InputRunResults());

        std::string bin = int.toBinaryString(i);
        while (bin.length() < n)
            bin = "0" + bin;

        char[] chars = bin.toCharArray();


        boolean[] boolArray = new boolean[n];
        for (int j = 0; j < bin.size(); j++)
        {
            boolArray[j] = chars[j] == '0' ? true : false;
        }

        System.out.println(Arrays.toString(boolArray));
    }

    std::vector<bool> inputList;


    for (int x = 0; x < numInputNodes; x++)
    {
        results.push_back(InputRunResults());
        for (int y = 0; y < numInputNodes; y++)
        {
            results[x].in = inputList;
        }
    }
}

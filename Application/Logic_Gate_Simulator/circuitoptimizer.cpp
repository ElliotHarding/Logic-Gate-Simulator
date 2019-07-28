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
}

std::vector<Gate*> CircuitOptimizer::CuircuitFromBooleanAlgebra(std::string algebraicString)
{

}

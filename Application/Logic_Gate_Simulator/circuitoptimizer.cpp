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

    //Get inputs
    std::vector<Node*> inputNodes;
    for (Gate* g : gates)
    {
        if (!g->HasConnectedInputNodes())
            inputGates.push_back(g);
    }

    //Nothing to optimise
    if (inputGates.size() < 2)
        return "";

    //Get outputs
    std::vector<Gate*> outputGates;
    for (Gate* g : gates)
    {
        if(!g->HasConnectedOutputNodes())
            outputGates.push_back(g);
    }

    //Nothing to optimise
    if (outputGates.size() == 0)
        return "";

    //Check what happens when input values are changed
}

std::vector<Gate*> CircuitOptimizer::CuircuitFromBooleanAlgebra(std::string algebraicString)
{

}

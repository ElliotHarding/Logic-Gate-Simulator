#include "circuit.h"

#include "gate.h"
#include "GateToggle.h"
#include "GateReciever.h"
#include "gatecollection.h"

//////////////////////////////////////////////////////////////////////////
/// \brief Circuit::Circuit
/// \param numInputs
/// \param numOutputs
///
Circuit::Circuit(const unsigned int& numInputs, const unsigned int& numOutputs) :
    m_bDeleteGates(true)
{
    for(uint iInput = 0; iInput < numInputs; iInput++)
    {
        inputs.push_back(new GateToggle());
    }
    for(uint iOutput = 0; iOutput < numOutputs; iOutput++)
    {
        outputs.push_back(new GateReciever());
    }
}

Circuit::~Circuit()
{
    if(m_bDeleteGates)
    {
        for(Gate* g : mainGates)
        {
            delete g;
        }
        for(Gate* g : inputs)
        {
            delete g;
        }
        for(Gate* g : outputs)
        {
            delete g;
        }
    }
}

GateCollection* Circuit::createGateCollection()
{
    //Todo ~ not hard coded pos values...

    m_bDeleteGates = false;

    int inputY = 100;
    for(Gate* g : mainGates)
    {
        g->setPosition(300, inputY+=100);
    }

    GateCollection* pNewCircuit = new GateCollection(mainGates);

    inputY = 100;
    for(Gate* g : inputs)
    {
        g->setPosition(200, inputY+=100);
        pNewCircuit->AddGate(g);
    }

    inputY = 100;
    for(Gate* g : outputs)
    {
        g->setPosition(500, inputY+=100);
        pNewCircuit->AddGate(g);
    }

    return pNewCircuit;
}

void Circuit::deleteMainGates()
{
    for(Gate* g : mainGates)
    {
        delete g;
    }
    mainGates.clear();

    //Todo ~ find out why this is needed!
    for(Gate* g : inputs)
    {
        g->DetachNodes();
    }
    for(Gate* g : outputs)
    {
        g->DetachNodes();
    }
}

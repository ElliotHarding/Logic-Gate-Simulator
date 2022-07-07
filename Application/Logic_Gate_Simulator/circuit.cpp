#include "circuit.h"

#include "gate.h"
#include "GateToggle.h"
#include "GateReciever.h"
#include "gatecollection.h"

namespace Settings
{
const uint GapBetweenGates = 100;
}

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

void displaceLinkedGates(Gate* pParent, std::vector<Gate*>& gates, int& maxX)
{
    NodeIds nids = pParent->getOutputNodes()[0]->linkInfo();
    for(int id : nids.linkedIds)
    {
        for(Gate* pSubGate : gates)
        {
            Node* pNode;
            if(pSubGate->FindNodeWithId(id, pNode))
            {
                const int newX = pParent->position().x() + Settings::GapBetweenGates;
                if(pSubGate->position().x() < newX)
                {
                    pSubGate->setPosition(newX, pParent->position().y());
                    maxX = maxX < newX ? newX : maxX;
                }

                displaceLinkedGates(pSubGate, gates, maxX);
            }
        }
    }
}

GateCollection* Circuit::createGateCollection()
{
    m_bDeleteGates = false;

    for(Gate* g : mainGates)
    {
        g->setPosition(-1, -1);
    }

    GateCollection* pNewCircuit = new GateCollection(mainGates);

    int maxX = 0;
    int posY = 0;
    for(Gate* g : inputs)
    {
        g->setPosition(0, posY+=Settings::GapBetweenGates);
        pNewCircuit->AddGate(g);

        displaceLinkedGates(g, mainGates, maxX);
    }

    posY = 0;
    maxX+=Settings::GapBetweenGates;
    for(Gate* g : outputs)
    {
        g->setPosition(maxX, posY+=Settings::GapBetweenGates);
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

#include "circuit.h"
#include "textlabel.h"

namespace Settings
{
const uint GapBetweenGates = 100;
}

//////////////////////////////////////////////////////////////////////////
/// \brief Circuit::Circuit
/// \param numInputs
/// \param numOutputs
///
Circuit::Circuit(const std::vector<char>& inputLetters, const std::vector<char>& outputLetters) :
    m_bDeleteGates(true)
{
    for(const char& inputLetter : inputLetters)
    {
        inputs[inputLetter] = new GateToggle();
    }
    for(const char& outLetter : outputLetters)
    {
        outputs[outLetter] = new GateReciever();
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
        for(auto const& g : inputs)
        {
            delete g.second;
        }
        for(auto const& g : outputs)
        {
            delete g.second;
        }
    }
}

void displaceLinkedGates(Gate* pParent, std::vector<Gate*>& gates, int& maxX)
{
    NodeIds nids = pParent->getOutputNodes()[0]->linkInfo();
    for(int id : nids.linkedIds)
    {
        for(uint iSubGate = 0; iSubGate < gates.size(); iSubGate++)
        {
            Node* pNode;
            if(gates[iSubGate]->findNodeWithId(id, pNode))
            {
                const int newX = pParent->position().x() + Settings::GapBetweenGates;
                if(gates[iSubGate]->position().x() < newX)
                {
                    gates[iSubGate]->setPosition(newX + 20, pParent->position().y());
                    maxX = maxX < newX ? newX : maxX;
                }

                Gate* newParentGate = gates[iSubGate];
                gates.erase(gates.begin() + iSubGate);
                displaceLinkedGates(newParentGate, gates, maxX);
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

    int maxX = 300;
    int posY = 300;
    int offsetButSameX = 0;
    for(auto const& g : inputs)
    {
        g.second->setPosition(offsetButSameX, posY+=Settings::GapBetweenGates);
        pNewCircuit->addGate(g.second);

        TextLabel* pTextLabel = new TextLabel();
        pTextLabel->update(pTextLabel->getFont(), QString(g.first));
        g.second->addAttachedLabel(pTextLabel);

        offsetButSameX += 20;

        displaceLinkedGates(g.second, mainGates, maxX);
    }

    posY = 300;
    maxX+=Settings::GapBetweenGates;
    offsetButSameX = 0;
    for(auto const& g : outputs)
    {
        g.second->setPosition(maxX + offsetButSameX, posY+=Settings::GapBetweenGates);
        pNewCircuit->addGate(g.second);

        TextLabel* pTextLabel = new TextLabel();
        pTextLabel->update(pTextLabel->getFont(), QString(g.first));
        g.second->addAttachedLabel(pTextLabel);

        offsetButSameX += 20;
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
    for(auto const& g : inputs)
    {
        g.second->detachNodes();
    }
    for(auto const& g : outputs)
    {
        g.second->detachNodes();
    }
}

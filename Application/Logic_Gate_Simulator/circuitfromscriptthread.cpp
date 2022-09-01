#include "circuitfromscriptthread.h"

#include "allgates.h"
#include "circuit.h"

#include <QRandomGenerator>
#include <QDebug>
#include <cmath>

bool allUnlinkedNodesFromSameGate(const std::vector<Node*>& circuitOutsUnlinked, const std::vector<Node*>& circuitInsUnlinked)
{
    for(uint i = 0; i < circuitOutsUnlinked.size(); i++)
    {
        for(uint j = 0; j < circuitInsUnlinked.size(); j++)
        {
            if(circuitOutsUnlinked[i]->GetParent() != circuitInsUnlinked[j]->GetParent())
            {
                return false;
            }
        }
    }
    return true;
}

Gate* genRandomGate(const uint& percentageNewGate)
{
    uint randomPercentage = QRandomGenerator::global()->generateDouble() * 100;
    if(randomPercentage < percentageNewGate)
    {
        int random = QRandomGenerator::global()->generateDouble() * 4;
        switch (random)
        {
        case 0:
            return new GateAnd();
        case 1:
            return new GateOr();
        case 2:
            return new GateNot();
        case 3:
            return new GateEor();
        default:
            return nullptr;
        }
    }

    return nullptr;
}


bool createRandomCircuit(Circuit& circuit, const uint& percentageNewGate, const uint& maxGates)
{
    circuit.deleteMainGates();

    std::vector<Node*> circuitOutsUnlinked;
    for(Gate* g : circuit.inputs)
    {
        circuitOutsUnlinked.push_back(g->getOutputNodes()[0]);
    }

    std::vector<Node*> circuitInsUnlinked;
    for(Gate* g : circuit.outputs)
    {
        circuitInsUnlinked.push_back(g->getInputNodes()[0]);
    }

    while(circuitInsUnlinked.size() > 0 || circuitOutsUnlinked.size() > 0)
    {
        Gate* newGate = genRandomGate(percentageNewGate);
        if(newGate != nullptr)
        {
            circuit.mainGates.push_back(newGate);

            if(circuit.mainGates.size() > maxGates)
                return false;

            const std::vector<Node*> inNodes = newGate->getInputNodes();
            for(Node* inNode : inNodes)
            {
                circuitInsUnlinked.push_back(inNode);
            }
            const std::vector<Node*> outNodes = newGate->getOutputNodes();
            for(Node* outNode : outNodes)
            {
                circuitOutsUnlinked.push_back(outNode);
            }
        }

        while(true)
        {
            if(circuitOutsUnlinked.size() > 0 && circuitInsUnlinked.size() > 0)
            {
                const int randomUnlinkedOut = QRandomGenerator::global()->generateDouble() * circuitOutsUnlinked.size();
                const int randomUnlinkedIn = QRandomGenerator::global()->generateDouble() * circuitInsUnlinked.size();

                if(circuitOutsUnlinked[randomUnlinkedOut]->GetParent() == circuitInsUnlinked[randomUnlinkedIn]->GetParent())
                {
                    if(allUnlinkedNodesFromSameGate(circuitOutsUnlinked, circuitInsUnlinked))
                        return false;
                    continue;
                }

                circuitOutsUnlinked[randomUnlinkedOut]->LinkNode(circuitInsUnlinked[randomUnlinkedIn]);
                circuitInsUnlinked[randomUnlinkedIn]->LinkNode(circuitOutsUnlinked[randomUnlinkedOut]);
                circuitOutsUnlinked.erase(circuitOutsUnlinked.begin() + randomUnlinkedOut);
                circuitInsUnlinked.erase(circuitInsUnlinked.begin() + randomUnlinkedIn);

                break;
            }
            else
            {
                return false;
            }
        }
    }

    return true;
}

bool testCircuitAgainstTruthTable(Circuit& circuit, TruthTable& truthTable)
{
    for (uint iTableRun = 0; iTableRun < truthTable.size; iTableRun++)
    {
        //Set inputs
        for (uint iInput = 0; iInput < circuit.inputs.size(); iInput++)
        {
            circuit.inputs[iInput]->SetPowerState(truthTable.inValues[iTableRun][iInput]);
        }

        //Update
        //Very inefficient... Todo ~ improve this
        for(uint iUpdate = 0; iUpdate < circuit.mainGates.size(); iUpdate++)
        {
            for(Gate* pGate : circuit.mainGates)
            {
                pGate->UpdateOutput();
            }
        }

        //Check outputs
        for(uint iOutput = 0; iOutput < circuit.outputs.size(); iOutput++)
        {
            if(circuit.outputs[iOutput]->GetValue() != truthTable.outValues[iTableRun][iOutput])
            {
                return false;
            }
        }
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
/// \brief CircuitFromScriptThread::CircuitFromScriptThread
///
CircuitFromScriptThread::CircuitFromScriptThread() : QThread()
{
}

void CircuitFromScriptThread::start(const uint& numInputs, const uint& numOutputs, const QString& script, const int& maxSeconds, const uint& percentageRandomGate, const uint& maxGates)
{
    m_numInputs = numInputs;
    m_numOutputs = numOutputs;
    m_script = script;
    m_maxSeconds = maxSeconds;
    m_percentageRandomGate = percentageRandomGate;
    m_maxGates = maxGates;

    QThread::start();
}

void CircuitFromScriptThread::run()
{
    const clock_t startTimeMs = clock();

    //Generate truth table from script
    TruthTable truthTable;
    if(Converter::scriptToTruthTable(m_script, m_numInputs, m_numOutputs, truthTable) != ConverterResult::SUCCESS)
    {
        emit circuitGenFailure("Failed to generate circuit!");
        return;
    }

    Circuit circuit(m_numInputs, m_numOutputs);

    //Begin generating random circuits until one matches truth table
    while(true)
    {
        if((clock() - startTimeMs)/1000 > m_maxSeconds)
        {
            emit circuitGenFailure("Failed to generate circuit!");
            return;
        }

        while(!createRandomCircuit(circuit, m_percentageRandomGate, m_maxGates))
        {
            if((clock() - startTimeMs)/1000 > m_maxSeconds)
            {
                emit circuitGenFailure("Failed to generate circuit!");
                return;
            }
        }

        //If random circuit matches truth table, circuit is complete.
        if(testCircuitAgainstTruthTable(circuit, truthTable))
        {
            emit circuitGenSuccess(circuit.createGateCollection());
            return;
        }
    }
}

#include "circuitfromtruthtablethread.h"

#include "circuit.h"
#include "allgates.h"

#include <QRandomGenerator>
#include <cmath>

namespace Settings
{
const char StartAlphabet = 'A';
const char EndAlphabet = 'Z';
}

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
    for(auto const& g : circuit.inputs)
    {
        circuitOutsUnlinked.push_back(g.second->getOutputNodes()[0]);
    }

    std::vector<Node*> circuitInsUnlinked;
    for(auto const& g : circuit.outputs)
    {
        circuitInsUnlinked.push_back(g.second->getInputNodes()[0]);
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
        for (auto const& inputGate : circuit.inputs)
        {
            //Todo ~ sort this out
            //   Can't confirm that all letters are there...
            uint iInput = inputGate.first - Settings::StartAlphabet;

            inputGate.second->SetPowerState(truthTable.inValues[iTableRun][iInput]);
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
        for(auto const& outputGate : circuit.outputs)
        {
            //Todo ~ sort this out
            //   Can't confirm that all letters are there...
            uint iOutput = Settings::EndAlphabet - outputGate.first;

            if(outputGate.second->GetValue() != truthTable.outValues[iTableRun][iOutput])
            {
                return false;
            }
        }
    }

    return true;
}

std::vector<char> getInputLetters(const uint iInputs)
{
    std::vector<char> result;
    for(uint i = 0; i < iInputs; i++)
    {
        result.push_back(Settings::StartAlphabet + i);
    }
    return result;
}

std::vector<char> getOutputLetters(const uint iOutputs)
{
    std::vector<char> result;
    for(uint i = 0; i < iOutputs; i++)
    {
        result.push_back(Settings::EndAlphabet - i);
    }
    return result;
}

//////////////////////////////////////////////////////////////////////////
/// \brief CircuitFromScriptThread::CircuitFromScriptThread
///
RandomCircuitGenThread::RandomCircuitGenThread() : QThread()
{
}

void RandomCircuitGenThread::start(const TruthTable& truthTable, const CircuitOptions& circuitGenOptions)
{
    m_truthTable = truthTable;
    m_circuitOptions = circuitGenOptions;

    QThread::start();
}

void RandomCircuitGenThread::run()
{
    const clock_t startTimeMs = clock();

    if(m_truthTable.inValues.empty() || m_truthTable.outValues.empty())
    {
        emit circuitGenFailure("Failed to generate circuit!");
        return;
    }

    const uint iInputs = m_truthTable.inValues[0].size();
    const uint iOutputs = m_truthTable.outValues[0].size();
    if(iInputs == 0 || iOutputs == 0)
    {
        emit circuitGenFailure("Failed to generate circuit!");
        return;
    }

    //Todo ~ TruthTable class should contains list of input/output letter names
    Circuit circuit(getInputLetters(iInputs), getOutputLetters(iOutputs));

    //Begin generating random circuits until one matches truth table
    while(true)
    {
        if((clock() - startTimeMs)/1000 > m_circuitOptions.m_maxSeconds)
        {
            emit circuitGenFailure("Failed to generate circuit!");
            return;
        }

        while(!createRandomCircuit(circuit, m_circuitOptions.m_percentageRandomGate, m_circuitOptions.m_maxGates))
        {
            if((clock() - startTimeMs)/1000 > m_circuitOptions.m_maxSeconds)
            {
                emit circuitGenFailure("Failed to generate circuit!");
                return;
            }
        }

        //If random circuit matches truth table, circuit is complete.
        if(testCircuitAgainstTruthTable(circuit, m_truthTable))
        {
            emit circuitGenSuccess(circuit.createGateCollection());
            return;
        }
    }
}

#include "dlg_editscript.h"
#include "ui_dlg_editscript.h"

#include "dlg_home.h"
#include "truthtable.h"
#include "GameObjects/gatefpga.h"
#include "allgates.h"
#include "gatefield.h"

#include <QRandomGenerator>
#include <QScriptEngine>
#include <QDebug>
#include <cmath>

namespace Settings
{
const uint MaxFailsForCircuitGen = 500;
const uint MaxFailsForCircuitGenCheck = 500;
const uint MaxGatesInCircuit = 10;
}

DLG_EditScript::DLG_EditScript(DLG_Home* pParent) :
    QDialog(pParent),
    ui(new Ui::DLG_EditScript),
    m_pDlgHome(pParent),
    m_pFpga(nullptr)
{
    ui->setupUi(this);
}

DLG_EditScript::~DLG_EditScript()
{
    delete ui;
}

void DLG_EditScript::open(GateFPGA* pFPGA)
{
    m_pFpga = pFPGA;

    if(m_pFpga)
    {
        const uint numInputs = m_pFpga->getNumInputs();
        setStartScript(numInputs);
        ui->spinBox_inputs->setValue(numInputs);

        const uint numOutputs = m_pFpga->getNumOutputs();
        setEndScript(numOutputs);
        ui->spinBox_outputs->setValue(numOutputs);

        ui->textEdit_script->setText(m_pFpga->getScript());
    }

    QDialog::open();
}

void DLG_EditScript::on_spinBox_inputs_valueChanged(int numInputs)
{
    setStartScript(numInputs);
}

void DLG_EditScript::on_spinBox_outputs_valueChanged(int numOutputs)
{
    setEndScript(numOutputs);
}

void DLG_EditScript::on_btn_setScript_clicked()
{
    if(m_pFpga)
    {
        m_pFpga->setInputs(ui->spinBox_inputs->value());
        m_pFpga->setOutputs(ui->spinBox_outputs->value());
        m_pFpga->setScript(ui->textEdit_script->toPlainText());
        m_pFpga = nullptr;
    }

    QDialog::close();
}

void DLG_EditScript::setStartScript(const uint& numInputs)
{
    QString inputValues = "";
    for(uint i = 1; i < numInputs+1; i++)
    {
        inputValues += "input" + QString::number(i) + ", ";
    }
    inputValues = inputValues.left(inputValues.length()-2);
    ui->lbl_startScript->setText("In vars: " + inputValues);
}

void DLG_EditScript::setEndScript(const uint& numOutputs)
{
    QString outputValues = "";
    for(uint i = 1; i < numOutputs+1; i++)
    {
        outputValues += "output" + QString::number(i) + ", ";
    }
    outputValues = outputValues.left(outputValues.length()-2);
    ui->lbl_endScript->setText("Out vars: " + outputValues);
}

void DLG_EditScript::onCircuitGenSucess(Circuit& circuit)
{
    GateCollection* pNewCircuit = circuit.createGateCollection();
    if(m_pFpga)
    {
        m_pFpga->GetParent()->AddGate(pNewCircuit);
        m_pFpga = nullptr;
    }
    else
    {
        m_pDlgHome->AddGateToGateField(pNewCircuit);
    }
    close();
}

std::vector<bool> genInputs(const uint& a, const uint& len)
{
    std::vector<bool> inputs;
    int mask = 1;
    for(uint i = 0; i < len; i++)
    {
        if((mask&a) >= 1)
            inputs.push_back(true);
        else
            inputs.push_back(false);
        mask<<=1;
    }
    return inputs;
}

Gate* genRandomGate()
{
    int random = QRandomGenerator::global()->generateDouble() * 10;
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
    case 4:
    case 5:
    case 6:
    default:
        return nullptr;
    }
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

bool createRandomCircuit(Circuit& circuit)
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
        Gate* newGate = genRandomGate();
        if(newGate != nullptr)
        {
            circuit.mainGates.push_back(newGate);

            if(circuit.mainGates.size() > Settings::MaxGatesInCircuit)
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

TruthTable genTruthTableFromScript(const QString& script, const uint& numInputs, const uint& numOutputs)
{
    TruthTable truthTable;

    QScriptEngine engine;
    QScriptContext* pContext = engine.pushContext();//I think this gets deleted by engine destructor

    std::vector<QString> inputVariables;
    for(uint i = 1; i <= numInputs; i++)
    {
        inputVariables.push_back("input" + QString::number(i));
    }

    std::vector<QString> outputVariables;
    for(uint i = 1; i <= numOutputs; i++)
    {
        outputVariables.push_back("input" + QString::number(i));
        pContext->activationObject().setProperty("output" + QString::number(i), false);
    }

    std::vector<bool> genInputValues;

    truthTable.size = pow(2, numInputs);
    for (uint iTableRun = 0; iTableRun < truthTable.size; iTableRun++)
    {
        //Generate input values
        genInputValues = genInputs(iTableRun, numInputs);
        truthTable.inValues.push_back(genInputValues);

        //Set input values for script
        for(uint iInput = 0; iInput < numInputs; iInput++)
        {
            pContext->activationObject().setProperty(inputVariables[iInput], (bool)genInputValues[iInput]);
        }

        //Run script
        engine.evaluate(script);

        //Collect output values from script
        std::vector<bool> genOutputValues;
        for(uint iOutput = 0; iOutput < numOutputs; iOutput++)
        {
            genOutputValues.push_back(pContext->activationObject().property(outputVariables[iOutput]).toBool());
        }
        truthTable.outValues.push_back(genOutputValues);
    }

    return truthTable;
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

void DLG_EditScript::on_btn_genCircuit_clicked()
{
    const uint numInputs = ui->spinBox_inputs->value();
    const uint numOutputs = ui->spinBox_outputs->value();
    const QString script = ui->textEdit_script->toPlainText();

    if(m_pFpga)
    {
        m_pFpga->setInputs(numInputs);
        m_pFpga->setOutputs(numOutputs);
        m_pFpga->setScript(script);
    }

    //Generate truth table from script
    TruthTable truthTable = genTruthTableFromScript(script, numInputs, numOutputs);

    Circuit circuit(numInputs, numOutputs);

    //Begin generating random circuits until one matches truth table
    uint testCounter = 0;
    while(true)
    {
        //Todo ~ make setting avaliable to user. Or do time setting.
        if(testCounter++ > Settings::MaxFailsForCircuitGenCheck)
        {
            m_pDlgHome->SendUserMessage("Failed to generate circuit!");
            return;
        }

        uint createCounter = 0;
        while(!createRandomCircuit(circuit))
        {
            //Todo ~ make setting avaliable to user. Or do time setting.
            if(createCounter++ > Settings::MaxFailsForCircuitGen)
            {
                m_pDlgHome->SendUserMessage("Failed to generate circuit!");
                return;
            }
        }

        //If random circuit matches truth table, circuit is complete.
        if(testCircuitAgainstTruthTable(circuit, truthTable))
        {
            onCircuitGenSucess(circuit);
            return;
        }
    }
}


//////////////////////////////////////////////////////////////////////////
/// \brief Circuit::Circuit
/// \param numInputs
/// \param numOutputs
///
Circuit::Circuit(const uint &numInputs, const uint &numOutputs) :
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

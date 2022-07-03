#include "dlg_editscript.h"
#include "ui_dlg_editscript.h"

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
const uint MaxGatesInCircuit = 10;
}

DLG_EditScript::DLG_EditScript(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DLG_EditScript),
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
    else
    {
        qDebug() << "DLG_ScriptEdit::on_btn_setScript_clicked - m_pFpga is nullptr";
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

bool createRandomCircuit(std::vector<Gate*>& circuit, std::vector<GateToggle*>& circuitInputs, std::vector<GateReciever*>& circuitOutputs)
{
    std::vector<Node*> circuitOutsUnlinked;
    for(Gate* g : circuitInputs)
    {
        circuitOutsUnlinked.push_back(g->getOutputNodes()[0]);
    }

    std::vector<Node*> circuitInsUnlinked;
    for(Gate* g : circuitOutputs)
    {
        circuitInsUnlinked.push_back(g->getInputNodes()[0]);
    }

    while(circuitInsUnlinked.size() > 0 || circuitOutsUnlinked.size() > 0)
    {
        Gate* newGate = genRandomGate();
        if(newGate != nullptr)
        {
            circuit.push_back(newGate);

            if(circuit.size() > Settings::MaxGatesInCircuit)
                return false;

            std::vector<Node*> inNodes = newGate->getInputNodes();
            for(Node* inNode : inNodes)
            {
                circuitInsUnlinked.push_back(inNode);
            }
            std::vector<Node*> outNodes = newGate->getOutputNodes();
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
                    bool different = false;
                    for(uint i = 0; i < circuitOutsUnlinked.size(); i++)
                    {
                        for(uint j = 0; j < circuitInsUnlinked.size(); j++)
                        {
                            if(circuitOutsUnlinked[i]->GetParent() != circuitInsUnlinked[j]->GetParent())
                            {
                                different = true;
                                break;
                            }
                        }
                        if(different)
                            break;
                    }
                    if(!different)
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

    const uint size = pow(2, numInputs);
    for (uint iTableRun = 0; iTableRun < size; iTableRun++)
    {
        //Generate input values
        std::vector<bool> genInputValues = genInputs(iTableRun, numInputs);
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

    //Generate truth table from fpga
    TruthTable truthTable = genTruthTableFromScript(script, numInputs, numOutputs);

    //Setup circuit inputs and outputs
    std::vector<Gate*> circuit;
    std::vector<GateToggle*> circuitInputs;
    std::vector<GateReciever*> circuitOutputs;
    for(uint iInput = 0; iInput < numInputs; iInput++)
    {
        circuitInputs.push_back(new GateToggle());
    }
    for(uint iOutput = 0; iOutput < numOutputs; iOutput++)
    {
        circuitOutputs.push_back(new GateReciever());
    }

    //Begin generating random circuits until one matches truth table
    while(true)
    {

        //Test circuit setup against truth table (inValues & outValues)
        bool validRun = true;
        for (uint iTableRun = 0; iTableRun < numInputs; iTableRun++)
        {

            //Set inputs
            for (uint iInput = 0; iInput < truthTable.inValues[iTableRun].size(); iInput++)
            {
                circuitInputs[iInput]->SetPowerState(truthTable.inValues[iTableRun][iInput]);
            }

            //Update
            //Very inefficient... Todo ~ improve this
            for(uint iUpdate = 0; iUpdate < circuit.size(); iUpdate++)
            {
                for(Gate* pGate : circuit)
                {
                    pGate->UpdateOutput();
                }
            }

            //Check outputs
            bool validOutputs = true;
            for(uint iOutput = 0; iOutput < truthTable.outValues[iTableRun].size(); iOutput++)
            {
                if(circuitOutputs[iOutput]->GetValue() != truthTable.outValues[iTableRun][iOutput])
                {
                    validOutputs = false;
                    break;
                }
            }

            if(!validOutputs)
            {
                validRun = false;
                break;
            }
        }

        //If random circuit matches truth table, circuit is complete.
        if(validRun)
        {
            GateCollection* pNewCircuit = new GateCollection(std::vector<Gate*>());
            int inputY = 100;
            for(Gate* g : circuit)
            {
                g->setPosition(300, inputY+=100);
                pNewCircuit->AddGate(g);
            }
            inputY = 100;
            for(Gate* g : circuitInputs)
            {
                g->setPosition(200, inputY+=100); //Todo ~ not hard coded values...
                pNewCircuit->AddGate(g);;
            }
            inputY = 100;
            for(Gate* g : circuitOutputs)
            {
                g->setPosition(500, inputY+=100);
                pNewCircuit->AddGate(g);
            }
            m_pFpga->GetParent()->AddGate(pNewCircuit);
            m_pFpga = nullptr;
            close();
            return;
        }

        //Prep a new circuit
        for(Gate* g : circuit)
        {
            delete g;
        }
        circuit.clear();
        for(Gate* g : circuitInputs)
        {
            g->DetachNodes();
        }
        for(Gate* g : circuitOutputs)
        {
            g->DetachNodes();
        }

        uint failCounter = 0;
        while(!createRandomCircuit(circuit, circuitInputs, circuitOutputs))
        {
            if(failCounter++ > Settings::MaxFailsForCircuitGen)
            {
                //Todo ~ warn of failure
                return;
            }

            //Prep a new circuit
            for(Gate* g : circuit)
            {
                delete g;
            }
            circuit.clear();
            for(Gate* g : circuitInputs)
            {
                g->DetachNodes();
            }
            for(Gate* g : circuitOutputs)
            {
                g->DetachNodes();
            }
        }
    }

}

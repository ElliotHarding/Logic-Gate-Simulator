#include "dlg_configurefpga.h"
#include "ui_dlg_configurefpga.h"

#include "GameObjects/gatefpga.h"
#include "allgates.h"
#include "gatefield.h"

#include <QRandomGenerator>
#include <QDebug>
#include <cmath>

namespace Settings
{
const uint MaxFailsForCircuitGen = 500;
const uint MaxGatesInCircuit = 10;
}

DLG_ConfigureFPGA::DLG_ConfigureFPGA(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DLG_ConfigureFPGA),
    m_pFpga(nullptr)
{
    ui->setupUi(this);
}

DLG_ConfigureFPGA::~DLG_ConfigureFPGA()
{
    delete ui;
}

void DLG_ConfigureFPGA::open(GateFPGA* pFPGA)
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

        QDialog::open();
    }
    else
    {
        qDebug() << "DLG_ConfigureFPGA::open - m_pFpga is nullptr";
    }
}

void DLG_ConfigureFPGA::on_spinBox_inputs_valueChanged(int numInputs)
{
    setStartScript(numInputs);
}

void DLG_ConfigureFPGA::on_spinBox_outputs_valueChanged(int numOutputs)
{
    setEndScript(numOutputs);
}

void DLG_ConfigureFPGA::on_btn_setScript_clicked()
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
        qDebug() << "DLG_ConfigureFPGA::on_btn_setScript_clicked - m_pFpga is nullptr";
    }

    QDialog::close();
}

void DLG_ConfigureFPGA::setStartScript(const uint& numInputs)
{
    QString inputValues = "";
    for(uint i = 1; i < numInputs+1; i++)
    {
        inputValues += "input" + QString::number(i) + ", ";
    }
    inputValues = inputValues.left(inputValues.length()-2);
    ui->lbl_startScript->setText("In vars: " + inputValues);
}

void DLG_ConfigureFPGA::setEndScript(const uint& numOutputs)
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

void genTruthTable(std::vector<std::vector<bool>>& inValues, std::vector<std::vector<bool>>& outValues, GateFPGA* pFpga)
{
    std::vector<Node*> inputNodes = pFpga->getInputNodes();
    std::vector<Node*> outputNodes = pFpga->getOutputNodes();

    const uint size = pow(2, inputNodes.size());
    for (uint i = 0; i < size; i++)
    {
        //Generate input values
        std::vector<bool> genInputValues = genInputs(i, inputNodes.size());
        inValues.push_back(genInputValues);

        //Set input nodes to generated values
        for (uint iNode = 0; iNode < genInputValues.size(); iNode++)
        {
            inputNodes[iNode]->setValue(genInputValues[iNode]);
        }

        //Run script
        pFpga->UpdateOutput();

        //Collect output node values
        std::vector<bool> genOutputValues;
        for(uint iNode = 0; iNode < outputNodes.size(); iNode++)
        {
            genOutputValues.push_back(outputNodes[iNode]->value());
        }
        outValues.push_back(genOutputValues);
    }
}

void DLG_ConfigureFPGA::on_btn_genCircuit_clicked()
{
    if(!m_pFpga)
    {
        qDebug() << "DLG_ConfigureFPGA::on_btn_genCircuit_clicked - m_pFpga is nullptr";
        return;
    }

    m_pFpga->setInputs(ui->spinBox_inputs->value());
    m_pFpga->setOutputs(ui->spinBox_outputs->value());
    m_pFpga->setScript(ui->textEdit_script->toPlainText());

    //Generate truth table from fpga
    std::vector<std::vector<bool>> inValues;
    std::vector<std::vector<bool>> outValues;
    genTruthTable(inValues, outValues, m_pFpga);

    //Setup circuit inputs and outputs
    std::vector<Gate*> circuit;
    std::vector<GateToggle*> circuitInputs;
    std::vector<GateReciever*> circuitOutputs;
    for(int iInput = 0; iInput < ui->spinBox_inputs->value(); iInput++)
    {
        circuitInputs.push_back(new GateToggle());
    }
    for(int iOutput = 0; iOutput < ui->spinBox_outputs->value(); iOutput++)
    {
        circuitOutputs.push_back(new GateReciever());
    }

    //Begin generating random circuits until one matches truth table
    while(true)
    {

        //Test circuit setup against truth table (inValues & outValues)
        bool validRun = true;
        for (uint iTableRun = 0; iTableRun < inValues.size(); iTableRun++)
        {

            //Set inputs
            for (uint iInput = 0; iInput < inValues[iTableRun].size(); iInput++)
            {
                circuitInputs[iInput]->SetPowerState(inValues[iTableRun][iInput]);
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
            for(uint iOutput = 0; iOutput < outValues[iTableRun].size(); iOutput++)
            {
                if(circuitOutputs[iOutput]->GetValue() != outValues[iTableRun][iOutput])
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
            for(Gate* g : circuit)
            {
                g->setPosition(300, 300);
                pNewCircuit->AddGate(g);
            }
            for(Gate* g : circuitInputs)
            {
                g->setPosition(300, 300);
                pNewCircuit->AddGate(g);;
            }
            for(Gate* g : circuitOutputs)
            {
                g->setPosition(300, 300);
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

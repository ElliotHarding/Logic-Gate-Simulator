#include "dlg_configurefpga.h"
#include "ui_dlg_configurefpga.h"

#include "GameObjects/gatefpga.h"
#include "allgates.h"

#include <QDebug>
#include <cmath>

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
#include "gatefield.h"
#include <QRandomGenerator>

Gate* genRandomGate()
{
    int random = QRandomGenerator::global()->generateDouble() * 7;
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

void DLG_ConfigureFPGA::on_btn_genCircuit_clicked()
{
    if(!m_pFpga)
    {
        qDebug() << "DLG_ConfigureFPGA::on_btn_genCircuit_clicked - m_pFpga is nullptr";
        return;
    }
    std::vector<std::vector<bool>> inValues;
    std::vector<std::vector<bool>> outValues;

    m_pFpga->setInputs(ui->spinBox_inputs->value());
    m_pFpga->setOutputs(ui->spinBox_outputs->value());
    m_pFpga->setScript(ui->textEdit_script->toPlainText());

    std::vector<Node*> inputNodes = m_pFpga->getInputNodes();
    std::vector<Node*> outputNodes = m_pFpga->getOutputNodes();

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
        m_pFpga->UpdateOutput();

        //Collect output node values
        std::vector<bool> genOutputValues;
        for(uint iNode = 0; iNode < outputNodes.size(); iNode++)
        {
            genOutputValues.push_back(outputNodes[iNode]->value());
        }
        outValues.push_back(genOutputValues);
    }


    std::vector<Gate*> circuit;
    std::vector<GateToggle*> circuitInputs;
    std::vector<GateReciever*> circuitOutputs;

    for(uint iInput = 0; iInput < inputNodes.size(); iInput++)
    {
        circuitInputs.push_back(new GateToggle());
    }

    for(uint iOutput = 0; iOutput < outputNodes.size(); iOutput++)
    {
        circuitOutputs.push_back(new GateReciever());
    }

    while(true)
    {
        bool validRun = true;
        for (uint iTableRun = 0; iTableRun < inValues.size(); iTableRun++)
        {

            //Set inputs
            for (uint iInput = 0; iInput < inValues[iTableRun].size(); iInput++)
            {
                circuitInputs[iInput]->SetPowerState(inValues[iTableRun][iInput]);
            }

            //Update
            for(uint iUpdate = 0; iUpdate < inputNodes.size(); iUpdate++)
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

        if(validRun)
        {
            for(Gate* g : circuit)
            {
                g->setPosition(300, 300);
                m_pFpga->GetParent()->AddGate(g);
            }
            for(Gate* g : circuitInputs)
            {
                g->setPosition(300, 300);
                m_pFpga->GetParent()->AddGate(g);
            }
            for(Gate* g : circuitOutputs)
            {
                g->setPosition(300, 300);
                m_pFpga->GetParent()->AddGate(g);
            }
            return;
        }

        for(Gate* g : circuit)
        {
            delete g;
        }
        circuit.clear();


        std::vector<Node*> circuitOuts;
        std::vector<Node*> circuitOutsUnlinked;
        for(Gate* g : circuitInputs)
        {
            circuitOuts.push_back(g->getOutputNodes()[0]);
            circuitOutsUnlinked.push_back(g->getOutputNodes()[0]);
        }

        std::vector<Node*> circuitIns;
        std::vector<Node*> circuitInsUnlinked;
        for(Gate* g : circuitOutputs)
        {
            circuitIns.push_back(g->getInputNodes()[0]);
            circuitInsUnlinked.push_back(g->getInputNodes()[0]);
        }

        while(circuitInsUnlinked.size() > 0 || circuitOutsUnlinked.size() > 0)
        {
            Gate* newGate = genRandomGate();
            if(newGate != nullptr)
            {
                circuit.push_back(newGate);

                if(circuit.size() > 5)
                    break;

                std::vector<Node*> inNodes = newGate->getInputNodes();
                for(Node* inNode : inNodes)
                {
                    circuitIns.push_back(inNode);
                    circuitInsUnlinked.push_back(inNode);
                }
                std::vector<Node*> outNodes = newGate->getOutputNodes();
                for(Node* outNode : outNodes)
                {
                    circuitOuts.push_back(outNode);
                    circuitOutsUnlinked.push_back(outNode);
                }
            }

            if(circuitOutsUnlinked.size() > 0)
            {
                const int randomUnlinkedOut = QRandomGenerator::global()->generateDouble() * circuitOutsUnlinked.size() - 1;
                const int randomIn = QRandomGenerator::global()->generateDouble() * circuitIns.size() - 1;

                circuitOutsUnlinked[randomUnlinkedOut]->LinkNode(circuitIns[randomIn]);
                circuitIns[randomIn]->LinkNode(circuitOutsUnlinked[randomUnlinkedOut]);
                circuitOutsUnlinked.erase(circuitOutsUnlinked.begin() + randomUnlinkedOut);
            }

            if(circuitInsUnlinked.size() > 0)
            {
                const int randomOut = QRandomGenerator::global()->generateDouble() * circuitOuts.size() - 1;
                const int randomUnlinkedIn = QRandomGenerator::global()->generateDouble() * circuitInsUnlinked.size() - 1;

                circuitOuts[randomOut]->LinkNode(circuitInsUnlinked[randomUnlinkedIn]);
                circuitInsUnlinked[randomUnlinkedIn]->LinkNode(circuitOuts[randomOut]);
                circuitInsUnlinked.erase(circuitInsUnlinked.begin() + randomUnlinkedIn);
            }
        }
    }

}

#include "dlg_configurefpga.h"
#include "ui_dlg_configurefpga.h"

#include "GameObjects/gatefpga.h"

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

std::list<bool> genInputs(const uint& a, const uint& len)
{
    std::list<bool> inputs;
    int mask = 1;
    for(uint i = 0; i < len; i++)
    {
        if((mask&a) >= 1)
            inputs.push_front(true);
        else
            inputs.push_front(false);
        mask<<=1;
    }
    return inputs;
}

void DLG_ConfigureFPGA::on_btn_genCircuit_clicked()
{
    if(!m_pFpga)
    {
        qDebug() << "DLG_ConfigureFPGA::on_btn_genCircuit_clicked - m_pFpga is nullptr";
        return;
    }
    std::list<std::list<bool>> inValues;
    std::list<std::list<bool>> outValues;

    m_pFpga->setInputs(ui->spinBox_inputs->value());
    m_pFpga->setOutputs(ui->spinBox_outputs->value());
    m_pFpga->setScript(ui->textEdit_script->toPlainText());

    std::vector<Node*> inputNodes = m_pFpga->getInputNodes();
    std::vector<Node*> outputNodes = m_pFpga->getOutputNodes();

    const uint size = pow(2, inputNodes.size());
    for (uint i = 0; i < size; i++)
    {
        //Generate input values
        std::list<bool> genInputValues = genInputs(i, inputNodes.size());
        inValues.push_back(genInputValues);

        //Set input nodes to generated values
        uint iNode = 0;
        for (std::list<bool>::iterator it = genInputValues.begin(); it != genInputValues.end(); ++it)
        {
            inputNodes[iNode]->setValue(*it);
            iNode++;
        }

        //Run script
        m_pFpga->UpdateOutput();

        //Collect output node values
        std::list<bool> genOutputValues;
        for(iNode = 0; iNode < outputNodes.size(); iNode++)
        {
            genOutputValues.push_back(outputNodes[iNode]->value());
        }
        outValues.push_back(genOutputValues);
    }

    BooleanExpression expression;

}

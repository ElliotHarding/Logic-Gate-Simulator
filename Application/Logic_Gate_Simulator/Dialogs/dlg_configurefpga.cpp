#include "dlg_configurefpga.h"
#include "ui_dlg_configurefpga.h"

#include "GameObjects/gatefpga.h"

#include <QDebug>

DLG_ConfigureFPGA::DLG_ConfigureFPGA(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DLG_ConfigureFPGA)
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
        inputValues += "input" + QString::number(i) + ",";
    }
    inputValues = inputValues.left(inputValues.length()-1);
    ui->lbl_startScript->setText("In vars: " + inputValues);
}

void DLG_ConfigureFPGA::setEndScript(const uint& numOutputs)
{
    QString outputValues = "";
    for(uint i = 1; i < numOutputs+1; i++)
    {
        outputValues += "output" + QString::number(i) + ",";
    }
    outputValues = outputValues.left(outputValues.length()-1);
    ui->lbl_endScript->setText("Out vars: " + outputValues);
}

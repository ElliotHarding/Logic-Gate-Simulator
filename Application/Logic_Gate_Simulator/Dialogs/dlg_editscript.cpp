#include "dlg_editscript.h"
#include "ui_dlg_editscript.h"

#include "dlg_home.h"
#include "gatereader.h"
#include "GameObjects/gatefpga.h"
#include "gatecollection.h"
#include "gatefield.h"
#include "circuitfromscriptthread.h"

#include <QDebug>

DLG_EditScript::DLG_EditScript(DLG_Home* pParent) :
    QDialog(pParent),
    ui(new Ui::DLG_EditScript),
    m_pDlgHome(pParent),
    m_pFpga(nullptr),
    m_pCircuitFromScriptThread(new CircuitFromScriptThread())
{
    ui->setupUi(this);

    connect(m_pCircuitFromScriptThread, SIGNAL(circuitGenSuccess(GateCollection*)), this, SLOT(onCircuitGenSuccess(GateCollection*)));
    connect(m_pCircuitFromScriptThread, SIGNAL(circuitGenFailure(const QString&)), this, SLOT(onCircuitGenFailure(const QString&)));
}

DLG_EditScript::~DLG_EditScript()
{
    delete m_pCircuitFromScriptThread;
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

        m_currentSavePath = "";
    }
    else
    {
        setStartScript(ui->spinBox_inputs->value());
        setEndScript(ui->spinBox_outputs->value());
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

void DLG_EditScript::onCircuitGenSuccess(GateCollection* pNewCircuit)
{
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

void DLG_EditScript::onCircuitGenFailure(const QString& failMessage)
{
    m_pDlgHome->SendUserMessage(failMessage);
}

void DLG_EditScript::on_btn_genCircuit_clicked()
{
    const uint numInputs = ui->spinBox_inputs->value();
    const uint numOutputs = ui->spinBox_outputs->value();
    const QString script = ui->textEdit_script->toPlainText();
    const int maxSeconds = ui->spinBox_maxGenTime->value();
    const uint percentageRandomGate = ui->spinBox_addGateChance->value();
    const uint maxGates = ui->spinBox_maxGates->value();

    if(m_pFpga)
    {
        m_pFpga->setInputs(numInputs);
        m_pFpga->setOutputs(numOutputs);
        m_pFpga->setScript(script);
    }

    if(m_pCircuitFromScriptThread->isRunning())
    {
        m_pDlgHome->SendUserMessage("Already generating!");
        return;
    }

    m_pCircuitFromScriptThread->start(numInputs, numOutputs, script, maxSeconds, percentageRandomGate, maxGates);

    //Todo ~ show user that circuit gen is loading...
}

void DLG_EditScript::on_btn_genTuthTable_clicked()
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
    TruthTable truthTable = CircuitFromScriptThread::genTruthTableFromScript(script, numInputs, numOutputs);

    //Testing purposes
    m_pDlgHome->showTruthTable(truthTable);
}

void DLG_EditScript::on_btn_load_clicked()
{

}

void DLG_EditScript::on_btn_Save_clicked()
{
    Saver saver;

    const uint numInputs = ui->spinBox_inputs->value();
    const uint numOutputs = ui->spinBox_outputs->value();
    const QString script = ui->textEdit_script->toPlainText();
    if(!saver.saveScript(m_currentSavePath, script, numInputs, numOutputs, m_pDlgHome))
    {
        //Error messages already handled by saver...
    }
}

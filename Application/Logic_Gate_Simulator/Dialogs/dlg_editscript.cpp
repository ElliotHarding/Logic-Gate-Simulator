#include "dlg_editscript.h"
#include "ui_dlg_editscript.h"

#include "dlg_home.h"
#include "GameObjects/gatefpga.h"
#include "gatecollection.h"
#include "gatefield.h"
#include "circuitfromscriptthread.h"
#include "truthtable.h"

#include <QDebug>
#include <QFile>

namespace Settings
{
const QString XMLElement = "xml";

const QString ScriptFile = ".Script";
const QString ScriptElement = "Script";
const QString ScriptInputsAttribute = "Inputs";
const QString ScriptOutputsAttribute = "Outputs";
}

DLG_EditScript::DLG_EditScript(DLG_Home* pParent) :
    QDialog(pParent),
    ui(new Ui::DLG_EditScript),
    m_pDlgHome(pParent),
    m_pFpga(nullptr),
    m_pDlgLoadGates(new QFileDialog(this))
{
    ui->setupUi(this);
}

DLG_EditScript::~DLG_EditScript()
{
    delete m_pDlgLoadGates;
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

    GateCollection* pNewCircuit = new GateCollection(std::vector<Gate*>());
    if(BooleanExpressionCalculator::scriptToCircuit(script, numInputs, numOutputs, pNewCircuit) == ExpressionCalculatorResult::SUCCESS)
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
    else
    {
        delete pNewCircuit;
        m_pDlgHome->SendUserMessage("Check script format!");
    }
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
    TruthTable tt;
    if(BooleanExpressionCalculator::scriptToTruthTable(script, numInputs, numOutputs, tt) == ExpressionCalculatorResult::SUCCESS)
    {
        m_pDlgHome->showTruthTable(tt);
        close();
    }
    else
    {
        m_pDlgHome->SendUserMessage("Check script format!");
    }
}

void DLG_EditScript::on_btn_load_clicked()
{
    QStringList fileNames = m_pDlgLoadGates->getOpenFileNames(this);

    if(fileNames.size() != 1)
    {
        m_pDlgHome->SendUserMessage("Only one file can be selected.");
        return;
    }

    const QString filePath = fileNames[0];
    if(!filePath.contains(Settings::ScriptFile))
    {
        m_pDlgHome->SendUserMessage("File not in script format.");
        return;
    }

    QFile file(filePath);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        m_pDlgHome->SendUserMessage("Failed to open file.");
        return;
    }

    QDomDocument doc;
    doc.setContent(&file);

    QDomElement scriptElement = doc.firstChildElement(Settings::ScriptElement);
    if(scriptElement.isNull())
    {
        m_pDlgHome->SendUserMessage("Failed reading file.");
        file.close();
        return;
    }

    m_currentSavePath = filePath;

    const uint numInputs = scriptElement.attribute(Settings::ScriptInputsAttribute, "1").toUInt();
    ui->spinBox_inputs->setValue(numInputs);
    setStartScript(numInputs);

    const uint numOutputs = scriptElement.attribute(Settings::ScriptOutputsAttribute, "1").toUInt();
    ui->spinBox_outputs->setValue(numOutputs);
    setEndScript(numOutputs);

    const QString script = scriptElement.text();
    ui->textEdit_script->setText(script);

    if(m_pFpga)
    {
        m_pFpga->setInputs(numInputs);
        m_pFpga->setOutputs(numOutputs);
        m_pFpga->setScript(script);
    }

    file.close();
}

void DLG_EditScript::on_btn_Save_clicked()
{
    const uint numInputs = ui->spinBox_inputs->value();
    const uint numOutputs = ui->spinBox_outputs->value();
    const QString script = ui->textEdit_script->toPlainText();

    QFile file(m_currentSavePath);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QString name;
        if(m_pDlgHome->requestUserInputString("Set save name", "Save name: ", name))
        {
            if(name.isEmpty())
            {
                m_pDlgHome->SendUserMessage("Invalid name!");
                return;
            }

            QString dir = QFileDialog::getExistingDirectory(m_pDlgHome, "Open Directory",
                                                         "/home",
                                                         QFileDialog::ShowDirsOnly
                                                         | QFileDialog::DontResolveSymlinks);
            m_currentSavePath = dir + "/" + name + Settings::ScriptFile;
            QFile file(m_currentSavePath);
            if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                m_pDlgHome->SendUserMessage("Can't open file to save!");
                return;
            }

            saveScriptFile(file, script, numInputs, numOutputs);
            return;
        }
        return;
    }

    saveScriptFile(file, script, numInputs, numOutputs);
}

void DLG_EditScript::saveScriptFile(QFile& file, const QString& script, const uint& numInputs, const uint& numOutputs)
{
    QDomDocument saveDoc(Settings::XMLElement);

    QDomElement scriptElement = saveDoc.createElement(Settings::ScriptElement);
    scriptElement.setAttribute(Settings::ScriptInputsAttribute, QString::number(numInputs));
    scriptElement.setAttribute(Settings::ScriptOutputsAttribute, QString::number(numOutputs));

    QDomText scriptNode = saveDoc.createTextNode(script);
    scriptElement.appendChild(scriptNode);

    saveDoc.appendChild(scriptElement);

    QTextStream stream(&file);
    stream << saveDoc.toString();

    file.close();
}

void DLG_EditScript::on_btn_genExpressions_clicked()
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

    std::vector<BooleanExpression> expressions;
    if(BooleanExpressionCalculator::scriptToBooleanExpressions(script, numInputs, numOutputs, expressions) == ExpressionCalculatorResult::SUCCESS)
    {
        m_pDlgHome->showBooleanExpressions(expressions);
        close();
    }
    else
    {
        m_pDlgHome->SendUserMessage("Failed to convert to boolean expression. Check format.");
    }
}

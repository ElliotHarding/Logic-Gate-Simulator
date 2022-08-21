#include "dlg_truthtable.h"
#include "ui_dlg_truthtable.h"
#include "dlg_home.h"
#include "circuitfromscriptthread.h"
#include "gatecollection.h"

#include <QDebug>

namespace Settings
{
const QRect TableDimensions = QRect(50, 50, 300, 300);

const uint IntStartAlphabet = 65;
const uint IntEndAlphabet = 121;
}

DLG_TruthTable::DLG_TruthTable(DLG_Home* pParent) :
    QDialog(pParent),
    ui(new Ui::DLG_TruthTable),
    m_pHome(pParent),
    m_pCircuitFromTruthTableThread(new CircuitFromTruthTableThread())
{
    ui->setupUi(this);

    connect(m_pCircuitFromTruthTableThread, SIGNAL(circuitGenSuccess(GateCollection*)), this, SLOT(onCircuitGenSuccess(GateCollection*)));
    connect(m_pCircuitFromTruthTableThread, SIGNAL(circuitGenFailure(const QString&)), this, SLOT(onCircuitGenFailure(const QString&)));
}

DLG_TruthTable::~DLG_TruthTable()
{
    clearUI();

    delete m_pCircuitFromTruthTableThread;
    delete ui;
}

void DLG_TruthTable::open(const TruthTable& truthTable)
{
    if(truthTable.inValues.empty() || truthTable.outValues.empty())
    {
        qDebug() << "DLG_TruthTable::open - incorrect truth table format!";
        return;
    }

    setTruthTable(truthTable);
}

void DLG_TruthTable::clearUI()
{
    for(QLabel* pLbl : m_tableLabels)
    {
        delete pLbl;
    }
    m_tableLabels.clear();

    for(std::vector<OutputLabel*> outLblCol : m_tableOutputLabels)
    {
        for(OutputLabel* pOutLbl : outLblCol)
        {
            delete pOutLbl;
        }
        outLblCol.clear();
    }
    m_tableOutputLabels.clear();

}

void DLG_TruthTable::setTruthTable(const TruthTable& truthTable)
{
    m_truthTable = truthTable;

    const uint iInputs = truthTable.inValues[0].size();
    const uint iOutputs = truthTable.outValues[0].size();
    const uint iIterations = truthTable.inValues.size();
    const uint iCols = iInputs + iOutputs;

    const uint labelWidth = Settings::TableDimensions.width() / iCols;
    const uint labelHeight = Settings::TableDimensions.height() / (iIterations + 1);

    for(uint iCol = 0; iCol < iCols; iCol++)
    {
        QLabel* newLabel;
        QString colTitle;
        if(iCol < iInputs)
        {
            //A, B, C...
            colTitle = QString(char(Settings::IntStartAlphabet+iCol));

            for(uint iRow = 0; iRow < iIterations; iRow++)
            {
                QLabel* rowLabel = new QLabel(QString::number(truthTable.inValues[iRow][iCol]), this);
                rowLabel->setGeometry(Settings::TableDimensions.x() + iCol * labelWidth, Settings::TableDimensions.y() + (iRow * labelHeight) + labelHeight, labelWidth, labelHeight);
                rowLabel->setAlignment(Qt::AlignCenter);
                m_tableLabels.push_back(rowLabel);
            }
        }
        else
        {
            //X, Y, Z...
            colTitle = QString(char(Settings::IntEndAlphabet+iCol-iInputs));

            std::vector<OutputLabel*> outLbls;
            for(uint iRow = 0; iRow < iIterations; iRow++)
            {
                OutputLabel* rowLabel = new OutputLabel(this, truthTable.outValues[iRow][iCol-iInputs]);
                rowLabel->setGeometry(Settings::TableDimensions.x() + iCol * labelWidth, Settings::TableDimensions.y() + (iRow * labelHeight) + labelHeight, labelWidth, labelHeight);
                rowLabel->setAlignment(Qt::AlignCenter);
                outLbls.push_back(rowLabel);
            }
            m_tableOutputLabels.push_back(outLbls);
        }

        newLabel = new QLabel(colTitle, this);
        newLabel->setGeometry(Settings::TableDimensions.x() + iCol * labelWidth, Settings::TableDimensions.y(), labelWidth, labelHeight);
        newLabel->setStyleSheet("border-color: black;");
        newLabel->setAlignment(Qt::AlignCenter);
        m_tableLabels.push_back(newLabel);
    }

    QDialog::open();
}

void DLG_TruthTable::close()
{
    clearUI();

    QDialog::close();
}

void DLG_TruthTable::closeEvent(QCloseEvent* e)
{
    clearUI();

    QDialog::closeEvent(e);
}

void DLG_TruthTable::on_btn_circuit_clicked()
{
    if(m_pCircuitFromTruthTableThread->isRunning())
    {
        m_pHome->SendUserMessage("Already generating!");
        return;
    }

    //Todo expose to user interface
    const uint maxSeconds = 100;
    const uint percentageRandomGate = 30;
    const uint maxGates = 10;

    if(!m_pCircuitFromTruthTableThread->start(m_truthTable, maxSeconds, percentageRandomGate, maxGates))
    {
        m_pHome->SendUserMessage("Failed to convert to circuit. Check format.");
    }
}

void DLG_TruthTable::on_btn_expressions_clicked()
{
    std::vector<BooleanExpression> expressions;
    ExpressionCalculatorResult result = BooleanExpressionCalculator::truthTableToBooleanExpressions(m_truthTable, expressions);
    if(result == ExpressionCalculatorResult::SUCCESS)
    {
        m_pHome->showBooleanExpressions(expressions);
        close();
    }
    else
    {
        m_pHome->SendUserMessage("Failed to convert to boolean expression. Check format.");
    }
}

void DLG_TruthTable::onCircuitGenSuccess(GateCollection* pNewCircuit)
{
    m_pHome->AddGateToGateField(pNewCircuit);
    close();
}

void DLG_TruthTable::onCircuitGenFailure(const QString& failMessage)
{
    m_pHome->SendUserMessage(failMessage);
}

/////////////////////////////////////////////////////////////////////////////
/// \brief OutputLabel::OutputLabel
/// \param pDlgTruthTable
/// \param value
///
OutputLabel::OutputLabel(DLG_TruthTable* pDlgTruthTable, const bool& value) : QLabel(pDlgTruthTable)
{
    setText(value ? "1" : "0");
}

bool OutputLabel::value() const
{
    return text() == "1";
}

void OutputLabel::mousePressEvent(QMouseEvent*)
{
    setText(text() == "1" ? "0" : "1");
}

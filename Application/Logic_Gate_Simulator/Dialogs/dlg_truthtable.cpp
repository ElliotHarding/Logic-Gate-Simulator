#include "dlg_truthtable.h"
#include "ui_dlg_truthtable.h"

#include "dlg_home.h"

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
    m_pHome(pParent)
{
    ui->setupUi(this);
}

DLG_TruthTable::~DLG_TruthTable()
{
    for(QLabel* pLbl : m_tableLabels)
    {
        delete pLbl;
    }

    delete ui;
}

void DLG_TruthTable::open(const TruthTable& truthTable)
{
    if(truthTable.inValues.empty() || truthTable.outValues.empty())
    {
        qDebug() << "DLG_TruthTable::open - incorrect truth table format!";
        return;
    }

    m_truthTable = truthTable;

    const uint iInputs = truthTable.inValues[0].size();
    const uint iOutputs = truthTable.outValues[0].size();
    const uint iIterations = truthTable.inValues.size();
    const uint iCols = iInputs + iOutputs;

    const uint labelWidth = Settings::TableDimensions.width() / iCols;
    const uint labelHeight = Settings::TableDimensions.height() / (iIterations + 1);
    qDebug() << iIterations;
    qDebug() << labelHeight;

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

            for(uint iRow = 0; iRow < iIterations; iRow++)
            {
                QLabel* rowLabel = new QLabel(QString::number(truthTable.outValues[iRow][iCol-iInputs]), this);
                rowLabel->setGeometry(Settings::TableDimensions.x() + iCol * labelWidth, Settings::TableDimensions.y() + (iRow * labelHeight) + labelHeight, labelWidth, labelHeight);
                rowLabel->setAlignment(Qt::AlignCenter);
                m_tableLabels.push_back(rowLabel);
            }
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
    for(QLabel* pLbl : m_tableLabels)
    {
        delete pLbl;
    }
    m_tableLabels.clear();

    QDialog::close();
}

void DLG_TruthTable::closeEvent(QCloseEvent* e)
{
    for(QLabel* pLbl : m_tableLabels)
    {
        delete pLbl;
    }
    m_tableLabels.clear();

    QDialog::closeEvent(e);
}

void DLG_TruthTable::on_btn_circuit_clicked()
{

}

void DLG_TruthTable::on_btn_expressions_clicked()
{
    std::vector<BooleanExpression> expressions;
    ExpressionCalculatorResult result = BooleanExpressionCalculator::truthTableToBooleanExpressions(m_truthTable, expressions);
    if(result == ExpressionCalculatorResult::SUCCESS)
    {
        m_pHome->showBooleanExpressions(expressions);
    }
    else
    {
        m_pHome->SendUserMessage("Failed to convert to boolean expression. Check format.");
    }
}

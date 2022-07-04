#include "dlg_truthtable.h"
#include "ui_dlg_truthtable.h"

#include <QDebug>

namespace Settings
{
const QRect TableDimensions = QRect(50, 50, 300, 300);
}

DLG_TruthTable::DLG_TruthTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DLG_TruthTable)
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
            colTitle = QString(char(65+iCol));

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
            colTitle = QString(char(120+iCol-iInputs));

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

#include "dlg_truthtable.h"
#include "ui_dlg_truthtable.h"
#include "dlg_home.h"
#include "gatecollection.h"
#include "converter.h"

#include <cmath>

namespace Settings
{
const QRect TableDimensions = QRect(50, 70, 300, 300);
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
    clearUI();
    delete ui;
}

void DLG_TruthTable::open(const TruthTable& truthTable)
{
    if(truthTable.inValues.empty() || truthTable.outValues.empty())
    {
        Logger::log(LL_Error, "DLG_TruthTable::open - incorrect truth table format!");
        return;
    }

    m_truthTable = truthTable;
    updateTableUI();
    QDialog::open();
}

void DLG_TruthTable::open()
{
    if(m_truthTable.size != 0 && m_truthTable.inValues.size() != 0 && m_truthTable.outValues.size() != 0)
    {
        QDialog::open();
        return;
    }


    //Create fresh truthtable
    TruthTable truthTable;
    truthTable.size = 4;
    for(uint i = 0; i < truthTable.size; i++)
    {
        truthTable.inValues.push_back(truthTable.genInputs(i, 2));
        truthTable.outValues.push_back({(i == (truthTable.size-1) ? true : false)});
    }
    truthTable.inLetters = {'A', 'B'};
    truthTable.outLetters = {'Z'};
    m_truthTable = truthTable;
    updateTableUI();
    QDialog::open();
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

void DLG_TruthTable::updateTableUI()
{
    const uint iInputs = m_truthTable.inValues[0].size();
    const uint iOutputs = m_truthTable.outValues[0].size();
    const uint iIterations = m_truthTable.inValues.size();
    const uint iCols = iInputs + iOutputs;

    ui->spinBox_inputs->setValue(iInputs);
    ui->spinBox_outputs->setValue(iOutputs);

    clearUI();

    const uint labelWidth = Settings::TableDimensions.width() / iCols;
    const uint labelHeight = Settings::TableDimensions.height() / (iIterations + 1);

    for(uint iCol = 0; iCol < iCols; iCol++)
    {
        QLabel* newLabel;
        QString colTitle;
        if(iCol < iInputs)
        {
            //A, B, C...
            colTitle = QString(m_truthTable.inLetters[iCol]);

            for(uint iRow = 0; iRow < iIterations; iRow++)
            {
                QLabel* rowLabel = new QLabel(QString::number(m_truthTable.inValues[iRow][iCol]), this);
                rowLabel->setGeometry(Settings::TableDimensions.x() + iCol * labelWidth, Settings::TableDimensions.y() + (iRow * labelHeight) + labelHeight, labelWidth, labelHeight);
                rowLabel->setAlignment(Qt::AlignCenter);
                rowLabel->show();
                m_tableLabels.push_back(rowLabel);
            }
        }
        else
        {
            //Z, Y, X...
            colTitle = QString(m_truthTable.outLetters[iCol-iInputs]);

            std::vector<OutputLabel*> outLbls;
            for(uint iRow = 0; iRow < iIterations; iRow++)
            {
                OutputLabel* rowLabel = new OutputLabel(this, m_truthTable.outValues[iRow][iCol-iInputs]);
                rowLabel->setGeometry(Settings::TableDimensions.x() + iCol * labelWidth, Settings::TableDimensions.y() + (iRow * labelHeight) + labelHeight, labelWidth, labelHeight);
                rowLabel->setAlignment(Qt::AlignCenter);
                rowLabel->show();
                outLbls.push_back(rowLabel);
            }
            m_tableOutputLabels.push_back(outLbls);
        }

        newLabel = new QLabel(colTitle, this);
        newLabel->setGeometry(Settings::TableDimensions.x() + iCol * labelWidth, Settings::TableDimensions.y(), labelWidth, labelHeight);
        newLabel->setStyleSheet("border-color: black;");
        newLabel->setAlignment(Qt::AlignCenter);
        newLabel->show();
        m_tableLabels.push_back(newLabel);
    }
}

void DLG_TruthTable::updateTruthTableFromUI()
{
    //Input values don't change from UI so m_truthTable.inValues are already done

    m_truthTable.outValues.clear();

    if(m_tableOutputLabels.size() == 0)
    {
        Logger::log(LL_Error, "DLG_TruthTable::updateTruthTableFromUI - m_tableOutputLabels has wrong size");
        m_pHome->sendUserMessage("Internal Error!"); //Todo make better error message
        return;
    }

    const uint iRows = m_tableOutputLabels[0].size();
    for(uint iRow = 0; iRow < iRows; iRow++)
    {
        std::vector<bool> rowValues;
        for(uint iCol = 0; iCol < m_tableOutputLabels.size(); iCol++)
        {
            rowValues.push_back(m_tableOutputLabels[iCol][iRow]->value());
        }
        m_truthTable.outValues.push_back(rowValues);
    }
}

void DLG_TruthTable::on_btn_circuit_clicked()
{
    updateTruthTableFromUI();

    //Todo ~ could move this logic into DLG_Home
    if(m_pHome->getCurrentConversionAlgorithm() == ConversionAlgorithm::Random)
    {
        m_pHome->runRandomConversionThread(m_truthTable, GoalResult::GR_Circuit);
    }
    else
    {
        GateCollection* pNewGateCollection = new GateCollection(std::vector<Gate*>());
        if(Converter::truthTableToCircuit(m_truthTable, m_pHome->getCircuitGenOptions(), pNewGateCollection) == ConverterResult::SUCCESS)
        {
            m_pHome->showGeneratedCircuit(pNewGateCollection);
        }
        else
        {
            delete pNewGateCollection;
            m_pHome->sendUserMessage("Failed to convert to circuit. Check format.");
        }
    }
}

void DLG_TruthTable::on_btn_expressions_clicked()
{
    updateTruthTableFromUI();

    if(m_pHome->getCurrentConversionAlgorithm() == ConversionAlgorithm::Random)
    {
        m_pHome->runRandomConversionThread(m_truthTable, GoalResult::GR_BooleanExpressions);
        return;
    }

    std::vector<BooleanExpression> expressions;
    ConverterResult result = Converter::truthTableToBooleanExpressions(m_truthTable, m_pHome->getCurrentConversionAlgorithm(), expressions);
    if(result == ConverterResult::SUCCESS)
    {
        m_pHome->showGeneratedBooleanExpressions(expressions);
    }
    else
    {
        m_pHome->sendUserMessage("Failed to convert to boolean expression. Check format.");
    }
}

void removeLetters(std::vector<char>& letters, const uint toRemove)
{
    for(int i = 0; i < toRemove; i++)
    {
        letters.erase(letters.begin());
    }
}

void DLG_TruthTable::on_spinBox_inputs_valueChanged(int value)
{
    if(m_truthTable.inValues.size() == 0)
    {
        m_pHome->sendUserMessage("Internal error!");//todo better message
        return;
    }

    //Add additional letters
    if(value > m_truthTable.inLetters.size())
    {
        uint extraLetters = value - m_truthTable.inLetters.size();
        m_truthTable.addInputLetters(extraLetters);
    }

    //Remove letters
    else if(value < m_truthTable.inLetters.size())
    {
        uint iRemove = m_truthTable.inLetters.size() - value;
        removeLetters(m_truthTable.inLetters, iRemove);
    }

    m_truthTable.inValues.clear();
    m_truthTable.size = pow(2, value);

    //Generate input values
    for (uint iTableRun = 0; iTableRun < m_truthTable.size; iTableRun++)
    {
        std::vector<bool> inputValues = m_truthTable.genInputs(iTableRun, value);
        m_truthTable.inValues.push_back(inputValues);
    }

    //Generate output values
    int difference = m_truthTable.size - m_truthTable.outValues[0].size() + 1;
    if(difference > 0)
    {
        for(uint iRow = m_truthTable.outValues.size() - 1; iRow < m_truthTable.size; iRow++)
        {
            std::vector<bool> row;
            for(uint iCol = 0; iCol < m_truthTable.outValues[iRow].size(); iCol++)
            {
                row.push_back(0);
            }
            m_truthTable.outValues.push_back(row);
        }
    }
    else if(difference < 0)
    {
        for(uint iRow = m_truthTable.size; iRow < m_truthTable.outValues.size(); iRow++)
        {
            m_truthTable.outValues.erase(m_truthTable.outValues.begin() + iRow);
        }
    }

    updateTableUI();
}

void DLG_TruthTable::on_spinBox_outputs_valueChanged(int value)
{
    if(m_truthTable.outValues.size() == 0)
    {
        m_pHome->sendUserMessage("Internal error!");//todo better message
        return;
    }

    //Add additional letters
    if(value > m_truthTable.outLetters.size())
    {
        uint extraLetters = value - m_truthTable.outLetters.size();
        m_truthTable.addOutputLetters(extraLetters);
    }

    //Remove letters
    else if(value < m_truthTable.outLetters.size())
    {
        uint iRemove = m_truthTable.outLetters.size() - value;
        removeLetters(m_truthTable.outLetters, iRemove);
    }

    int difference = value - m_truthTable.outValues[0].size();
    if(difference > 0)
    {
        for(uint iRow = 0; iRow < m_truthTable.outValues.size(); iRow++)
        {
            for(int i = m_truthTable.outValues[iRow].size(); i < value; i++)
            {
                m_truthTable.outValues[iRow].push_back(0);
            }
        }
    }
    else if(difference < 0)
    {
        for(uint iRow = 0; iRow < m_truthTable.outValues.size(); iRow++)
        {
            for(uint i = value - 1; i < m_truthTable.outValues[iRow].size(); i++)
            {
                m_truthTable.outValues[iRow].erase(m_truthTable.outValues[iRow].begin() + i);
            }
        }
    }

    updateTableUI();
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

#include "dlg_karnaughmap.h"
#include "ui_dlg_karnaughmap.h"
#include "dlg_home.h"

DLG_KarnaughMap::DLG_KarnaughMap(DLG_Home* pHome) :
    QDialog(pHome),
    ui(new Ui::DLG_KarnaughMap),
    m_pHome(pHome)
{
    ui->setupUi(this);
}

DLG_KarnaughMap::~DLG_KarnaughMap()
{
    delete ui;
}

void DLG_KarnaughMap::show(const KarnaughMap &kMap)
{
    m_kMap = kMap;
    clearUI();

    ui->spinBox_inputs->setValue(m_kMap.inputLetters.size());

    if(m_kMap.values.empty() || m_kMap.values[0].empty())
    {
        Logger::log(LogLevel::LL_Error, "DLG_KarnaughMap::show - Failed to show Karnaugh map.");
        return;
    }

    const uint labelWidth = Settings::TableDisplayDimensions.width() / (m_kMap.xInputs.size() + 1);
    const uint labelHeight = Settings::TableDisplayDimensions.height() / (m_kMap.yInputs.size() + 1);

    for(int iCol = 0; iCol < m_kMap.xInputs.size(); iCol++)
    {
        QString colTitle;
        for(int i = 0; i < m_kMap.xInputs[iCol].size(); i++)
        {
            colTitle += (m_kMap.xInputs[iCol][i].second ? "" : "!") + QString(m_kMap.xInputs[iCol][i].first) + " ";
        }

        QLabel* newLabel = new QLabel(colTitle, this);
        newLabel->setGeometry(Settings::TableDisplayDimensions.x() + (1 + iCol) * labelWidth, Settings::TableDisplayDimensions.y(), labelWidth, labelHeight);
        newLabel->setStyleSheet("border-color: black; font-weight: bold;");
        newLabel->setAlignment(Qt::AlignCenter);
        newLabel->show();
        m_tableLabels.push_back(newLabel);

        std::vector<OutputLabel*> outLbls;
        for(int iRow = 0; iRow < m_kMap.yInputs.size(); iRow++)
        {
            OutputLabel* rowLabel = new OutputLabel(this, m_kMap.values[iCol][iRow]);
            rowLabel->setGeometry(Settings::TableDisplayDimensions.x() + (1 + iCol) * labelWidth, Settings::TableDisplayDimensions.y() + (iRow * labelHeight) + labelHeight, labelWidth, labelHeight);
            rowLabel->setAlignment(Qt::AlignCenter);
            rowLabel->show();
            outLbls.push_back(rowLabel);
        }
        m_tableOutputLabels.push_back(outLbls);
    }

    for(int iRow = 0; iRow < m_kMap.yInputs.size(); iRow++)
    {
        QString rowTitle;
        for(int i = 0; i < m_kMap.yInputs[iRow].size(); i++)
        {
            rowTitle += (m_kMap.yInputs[iRow][i].second ? "" : "!") + QString(m_kMap.yInputs[iRow][i].first) + " ";
        }

        QLabel* newLabel = new QLabel(rowTitle, this);
        newLabel->setGeometry(Settings::TableDisplayDimensions.x(), Settings::TableDisplayDimensions.y() + labelHeight + (iRow * labelHeight), labelWidth, labelHeight);
        newLabel->setStyleSheet("border-color: black; font-weight: bold;");
        newLabel->setAlignment(Qt::AlignCenter);
        newLabel->show();
        m_tableLabels.push_back(newLabel);
    }

    QDialog::show();
}

void DLG_KarnaughMap::clearUI()
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

void DLG_KarnaughMap::on_btn_expressions_clicked()
{

}


void DLG_KarnaughMap::on_btn_circuit_clicked()
{

}


void DLG_KarnaughMap::on_btn_truthTable_clicked()
{

}


void DLG_KarnaughMap::on_spinBox_inputs_valueChanged(int arg1)
{

}


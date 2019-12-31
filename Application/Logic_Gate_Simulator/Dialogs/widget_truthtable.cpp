#include "widget_truthtable.h"
#include "ui_widget_truthtable.h"

Widget_TruthTable::Widget_TruthTable(int iInputs, int iOutputs, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget_TruthTable)
{
    ui->setupUi(this);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::white);
    setPalette(pal);

    //Calculate number of rows
    int numRows = 0;
    if(iInputs == 1)
        numRows = 2;
    else if(iInputs == 2)
        numRows = 4;
    else if(iInputs == 3)
        numRows = 8;
    else if(iInputs == 4)
        numRows = 24;
    else
        numRows = 0;

    const int numCols = iInputs + iOutputs;
    const int lblWidth = geometry().x()/numCols;
    const int lblHeight = geometry().y()/(numRows+1); //+1 for title labels

    //make titles
    for (int iCol = 0; iCol < numCols; iCol++)
    {
        QLabel* newLabel;
        if(iCol <= iInputs)
        {
            //A, B, C...
            newLabel = new QLabel(QString(char(52+iCol)) ,this);
        }
        else
        {
            //X, Y, Z...
            newLabel = new QLabel(QString(char(120+iCol-iInputs)) ,this);
        }

        newLabel->setGeometry(iCol * lblWidth, 0, lblWidth, lblHeight);
        m_labelBin.push_back(newLabel);
    }

    //Input values
    for(int iCol = 0; iCol < iInputs; iCol++)
    {
        for (int iRow = 0; iRow < numRows; iRow++)
        {
            QLabel* newLabel = new QLabel("0", this);
            newLabel->setGeometry(iCol * lblWidth, iRow * lblHeight + lblHeight, lblWidth, lblHeight);
            m_labelBin.push_back(newLabel);
        }

    }

    //Result rows
    for(int iCol = iInputs+1; iCol < numCols; iCol++)
    {
        std::vector<BinaryLabel*> resultLabels;
        for(int iRow = 0; iRow < numRows; iRow++)
        {
            BinaryLabel* newLabel = new BinaryLabel(this);
            newLabel->setGeometry(iCol * lblWidth, iRow * lblHeight + lblHeight, lblWidth, lblHeight);
            resultLabels.push_back(newLabel);
        }

        m_resultLabels.push_back(resultLabels);
    }
}

Widget_TruthTable::~Widget_TruthTable()
{
    for (size_t index = 0; index < m_labelBin.size(); index++)
    {
        delete m_labelBin[index];
    }

    for (size_t iVector = 0; iVector < m_resultLabels.size(); iVector++)
    {
        for(size_t index = 0; index < m_resultLabels[iVector].size(); index++)
        {
            delete m_resultLabels[iVector][index];
        }
    }

    delete ui;
}

void Widget_TruthTable::SetResults(std::vector<std::vector<bool>> results)
{
    for (size_t iVector = 0; iVector < m_resultLabels.size(); iVector++)
    {
        for(size_t index = 0; index < m_resultLabels[iVector].size(); index++)
        {
            m_resultLabels[iVector][index]->SetValue(results[iVector][index]);
        }
    }
    DisableTextEdit();
}

std::vector<std::vector<bool>> Widget_TruthTable::GetAnswer()
{
    std::vector<std::vector<bool>> res;
    for (size_t iVector = 0; iVector < m_resultLabels.size(); iVector++)
    {
        std::vector<bool> nestedRes;
        for(size_t index = 0; index < m_resultLabels[iVector].size(); index++)
        {
            nestedRes.push_back(m_resultLabels[iVector][index]->GetValue());
        }
        res.push_back(nestedRes);
    }
    return res;
}

void Widget_TruthTable::DisableTextEdit()
{
    for (size_t iVector = 0; iVector < m_resultLabels.size(); iVector++)
    {
        for(size_t index = 0; index < m_resultLabels[iVector].size(); index++)
        {
            m_resultLabels[iVector][index]->Disable();
        }
    }
}

BinaryLabel::BinaryLabel(QWidget *parent) : QLabel(parent)
{
}

void BinaryLabel::SetValue(bool value)
{
    setText(value ? "1" : "0");
}

bool BinaryLabel::GetValue()
{
    return text() == "1";
}

void BinaryLabel::Disable()
{
    m_bDisabled = true;
}

void BinaryLabel::mousePressEvent(QMouseEvent *ev)
{
    if(!m_bDisabled)
        QLabel::setText(text() == "0" ? "1" : "0");
    QLabel::mousePressEvent(ev);
}

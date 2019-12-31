#include "widget_tripleinputtruthtable.h"
#include "ui_widget_tripleinputtruthtable.h"

Widget_TripleInputTruthTable::Widget_TripleInputTruthTable(QWidget *parent) :
    TruthTableWidgetBase(parent),
    ui(new Ui::Widget_TripleInputTruthTable)
{
    ui->setupUi(this);

    m_pLblResult1 = new BinaryLabel(this);
    m_pLblResult2 = new BinaryLabel(this);
    m_pLblResult3 = new BinaryLabel(this);
    m_pLblResult4 = new BinaryLabel(this);
    m_pLblResult5 = new BinaryLabel(this);
    m_pLblResult6 = new BinaryLabel(this);
    m_pLblResult7 = new BinaryLabel(this);
    m_pLblResult8 = new BinaryLabel(this);

    m_pLblResult1->setGeometry(170, 70, 31, 21);
    m_pLblResult2->setGeometry(170, 100, 31, 21);
    m_pLblResult3->setGeometry(170, 130, 31, 21);
    m_pLblResult4->setGeometry(170, 160, 31, 21);
    m_pLblResult5->setGeometry(170, 190, 31, 21);
    m_pLblResult6->setGeometry(170, 220, 31, 21);
    m_pLblResult7->setGeometry(170, 250, 31, 21);
    m_pLblResult8->setGeometry(170, 280, 31, 21);

    m_pLblResult1->show();
    m_pLblResult2->show();
    m_pLblResult3->show();
    m_pLblResult4->show();
    m_pLblResult5->show();
    m_pLblResult6->show();
    m_pLblResult7->show();
    m_pLblResult8->show();
}

Widget_TripleInputTruthTable::~Widget_TripleInputTruthTable()
{
    delete ui;
}

void Widget_TripleInputTruthTable::DisableTextEdit()
{
    m_pLblResult1->Disable();
    m_pLblResult2->Disable();
    m_pLblResult3->Disable();
    m_pLblResult4->Disable();
    m_pLblResult5->Disable();
    m_pLblResult6->Disable();
    m_pLblResult7->Disable();
    m_pLblResult8->Disable();
}

void Widget_TripleInputTruthTable::SetResults(bool results[])
{
    m_pLblResult1->SetValue(results[0]);
    m_pLblResult2->SetValue(results[1]);
    m_pLblResult3->SetValue(results[2]);
    m_pLblResult4->SetValue(results[3]);
    m_pLblResult5->SetValue(results[4]);
    m_pLblResult6->SetValue(results[5]);
    m_pLblResult7->SetValue(results[6]);
    m_pLblResult8->SetValue(results[7]);

    DisableTextEdit();
}

std::vector<bool> Widget_TripleInputTruthTable::GetResults()
{
    std::vector<bool> res;
    res.push_back(m_pLblResult1->GetValue());
    res.push_back(m_pLblResult1->GetValue());
    res.push_back(m_pLblResult3->GetValue());
    res.push_back(m_pLblResult4->GetValue());
    res.push_back(m_pLblResult5->GetValue());
    res.push_back(m_pLblResult6->GetValue());
    res.push_back(m_pLblResult7->GetValue());
    res.push_back(m_pLblResult8->GetValue());
    return res;
}

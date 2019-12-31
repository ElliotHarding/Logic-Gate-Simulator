#include "widget_doubleinputtruthtable.h"
#include "ui_widget_doubleinputtruthtable.h"
#include <QLayout>
Widget_DoubleInputTruthTable::Widget_DoubleInputTruthTable(QWidget *parent) :
    TruthTableWidgetBase(parent),
    ui(new Ui::Widget_DoubleInputTruthTable)
{
    ui->setupUi(this);

    m_pLblResult1 = new BinaryLabel(this);
    m_pLblResult2 = new BinaryLabel(this);
    m_pLblResult3 = new BinaryLabel(this);
    m_pLblResult4 = new BinaryLabel(this);

    m_pLblResult1->setGeometry(140, 110, 31, 21);
    m_pLblResult2->setGeometry(140, 140, 31, 21);
    m_pLblResult3->setGeometry(140, 170, 31, 21);
    m_pLblResult4->setGeometry(140, 200, 31, 21);

    m_pLblResult1->show();
    m_pLblResult2->show();
    m_pLblResult3->show();
    m_pLblResult4->show();
}

Widget_DoubleInputTruthTable::~Widget_DoubleInputTruthTable()
{
    delete ui;
}

void Widget_DoubleInputTruthTable::SetResults(bool results[])
{
    m_pLblResult1->SetValue(results[0]);
    m_pLblResult2->SetValue(results[1]);
    m_pLblResult3->SetValue(results[2]);
    m_pLblResult4->SetValue(results[3]);

    DisableTextEdit();
}

std::vector<bool> Widget_DoubleInputTruthTable::GetResults()
{
    std::vector<bool> res;
    res.push_back(m_pLblResult1->GetValue());
    res.push_back(m_pLblResult1->GetValue());
    res.push_back(m_pLblResult3->GetValue());
    res.push_back(m_pLblResult4->GetValue());
    return res;
}

void Widget_DoubleInputTruthTable::DisableTextEdit()
{
    m_pLblResult1->Disable();
    m_pLblResult2->Disable();
    m_pLblResult3->Disable();
    m_pLblResult4->Disable();
}

#include "widget_doubleinputtruthtable.h"
#include "ui_widget_doubleinputtruthtable.h"
#include <QLayout>
Widget_DoubleInputTruthTable::Widget_DoubleInputTruthTable(QWidget *parent) :
    TruthTableWidgetBase(parent),
    ui(new Ui::Widget_DoubleInputTruthTable)
{
    ui->setupUi(this);

    BinaryLabel* m_pLblResult = new BinaryLabel();
    m_pLblResult->setGeometry(130, 110, 31, 21);

    QGridLayout* newLayout = new QGridLayout();
    m_pLblResult->raise();
    m_pLblResult->SetValue(1);
    newLayout->addWidget(m_pLblResult);

    setLayout(newLayout);

    ui->lb_result2 = new BinaryLabel(this);
    ui->lb_result3 = new BinaryLabel(this);
    ui->lb_result4 = new BinaryLabel(this);
}

Widget_DoubleInputTruthTable::~Widget_DoubleInputTruthTable()
{
    delete ui;
}

void Widget_DoubleInputTruthTable::SetResults(bool results[])
{
    //((BinaryLabel*)ui->lb_result1)->SetValue(results[0]);
    ((BinaryLabel*)ui->lb_result2)->SetValue(results[1]);
    ((BinaryLabel*)ui->lb_result3)->SetValue(results[2]);
    ((BinaryLabel*)ui->lb_result4)->SetValue(results[3]);
    DisableTextEdit();
}

std::vector<bool> Widget_DoubleInputTruthTable::GetResults()
{
    std::vector<bool> res;
    //res.push_back(((BinaryLabel*)ui->lb_result1)->GetValue());
    res.push_back(((BinaryLabel*)ui->lb_result2)->GetValue());
    res.push_back(((BinaryLabel*)ui->lb_result3)->GetValue());
    res.push_back(((BinaryLabel*)ui->lb_result4)->GetValue());
    return res;
}

void Widget_DoubleInputTruthTable::DisableTextEdit()
{
    //((BinaryLabel*)ui->lb_result1)->Disable();
    ((BinaryLabel*)ui->lb_result2)->Disable();
    ((BinaryLabel*)ui->lb_result3)->Disable();
    ((BinaryLabel*)ui->lb_result4)->Disable();
}

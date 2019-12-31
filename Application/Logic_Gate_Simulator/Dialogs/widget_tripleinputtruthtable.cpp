#include "widget_tripleinputtruthtable.h"
#include "ui_widget_tripleinputtruthtable.h"

Widget_TripleInputTruthTable::Widget_TripleInputTruthTable(QWidget *parent) :
    TruthTableWidgetBase(parent),
    ui(new Ui::Widget_TripleInputTruthTable)
{
    ui->setupUi(this);

    ui->lb_result1 = new BinaryLabel(this);
    ui->lb_result2 = new BinaryLabel(this);
    ui->lb_result3 = new BinaryLabel(this);
    ui->lb_result4 = new BinaryLabel(this);
    ui->lb_result5 = new BinaryLabel(this);
    ui->lb_result6 = new BinaryLabel(this);
    ui->lb_result7 = new BinaryLabel(this);
    ui->lb_result8 = new BinaryLabel(this);
}

Widget_TripleInputTruthTable::~Widget_TripleInputTruthTable()
{
    delete ui;
}

void Widget_TripleInputTruthTable::DisableTextEdit()
{
    ((BinaryLabel*)ui->lb_result1)->Disable();
    ((BinaryLabel*)ui->lb_result2)->Disable();
    ((BinaryLabel*)ui->lb_result3)->Disable();
    ((BinaryLabel*)ui->lb_result4)->Disable();
    ((BinaryLabel*)ui->lb_result5)->Disable();
    ((BinaryLabel*)ui->lb_result6)->Disable();
    ((BinaryLabel*)ui->lb_result7)->Disable();
    ((BinaryLabel*)ui->lb_result8)->Disable();
}

void Widget_TripleInputTruthTable::SetResults(bool results[])
{
    ((BinaryLabel*)ui->lb_result1)->SetValue(results[0]);
    ((BinaryLabel*)ui->lb_result2)->SetValue(results[1]);
    ((BinaryLabel*)ui->lb_result3)->SetValue(results[2]);
    ((BinaryLabel*)ui->lb_result4)->SetValue(results[3]);
    ((BinaryLabel*)ui->lb_result5)->SetValue(results[4]);
    ((BinaryLabel*)ui->lb_result6)->SetValue(results[5]);
    ((BinaryLabel*)ui->lb_result7)->SetValue(results[6]);
    ((BinaryLabel*)ui->lb_result8)->SetValue(results[7]);
    DisableTextEdit();
}

std::vector<bool> Widget_TripleInputTruthTable::GetResults()
{
    std::vector<bool> res;
    res.push_back(((BinaryLabel*)ui->lb_result1)->GetValue());
    res.push_back(((BinaryLabel*)ui->lb_result2)->GetValue());
    res.push_back(((BinaryLabel*)ui->lb_result3)->GetValue());
    res.push_back(((BinaryLabel*)ui->lb_result4)->GetValue());
    res.push_back(((BinaryLabel*)ui->lb_result5)->GetValue());
    res.push_back(((BinaryLabel*)ui->lb_result6)->GetValue());
    res.push_back(((BinaryLabel*)ui->lb_result7)->GetValue());
    res.push_back(((BinaryLabel*)ui->lb_result8)->GetValue());
    return res;
}

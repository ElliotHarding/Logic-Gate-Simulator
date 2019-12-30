#include "widget_doubleinputtruthtable.h"
#include "ui_widget_doubleinputtruthtable.h"

Widget_DoubleInputTruthTable::Widget_DoubleInputTruthTable(QWidget *parent) :
    TruthTableWidgetBase(parent),
    ui(new Ui::Widget_DoubleInputTruthTable)
{
    ui->setupUi(this);
}

Widget_DoubleInputTruthTable::~Widget_DoubleInputTruthTable()
{
    delete ui;
}

void Widget_DoubleInputTruthTable::SetResults(bool results[])
{
    ui->tb_result1->setPlainText(results[0] ? "1" : "0");
    ui->tb_result2->setPlainText(results[0] ? "1" : "0");
    ui->tb_result3->setPlainText(results[0] ? "1" : "0");
    ui->tb_result4->setPlainText(results[0] ? "1" : "0");

    DisableTextEdit(true);
}

std::vector<bool> Widget_DoubleInputTruthTable::GetResults()
{
    std::vector<bool> res;
    res.push_back(ui->tb_result1->toPlainText() == "1");
    res.push_back(ui->tb_result2->toPlainText() == "1");
    res.push_back(ui->tb_result3->toPlainText() == "1");
    res.push_back(ui->tb_result4->toPlainText() == "1");
    return res;
}

void Widget_DoubleInputTruthTable::DisableTextEdit(bool disableTextEdit)
{
    ui->tb_result1->setDisabled(disableTextEdit);
    ui->tb_result2->setDisabled(disableTextEdit);
    ui->tb_result3->setDisabled(disableTextEdit);
    ui->tb_result4->setDisabled(disableTextEdit);
}

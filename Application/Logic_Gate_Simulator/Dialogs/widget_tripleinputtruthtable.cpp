#include "widget_tripleinputtruthtable.h"
#include "ui_widget_tripleinputtruthtable.h"

Widget_TripleInputTruthTable::Widget_TripleInputTruthTable(QWidget *parent) :
    TruthTableWidgetBase(parent),
    ui(new Ui::Widget_TripleInputTruthTable)
{
    ui->setupUi(this);
}

Widget_TripleInputTruthTable::~Widget_TripleInputTruthTable()
{
    delete ui;
}

void Widget_TripleInputTruthTable::DisableTextEdit(bool disableTextEdit)
{
    ui->tb_result1->setDisabled(disableTextEdit);
    ui->tb_result2->setDisabled(disableTextEdit);
    ui->tb_result3->setDisabled(disableTextEdit);
    ui->tb_result4->setDisabled(disableTextEdit);
    ui->tb_result5->setDisabled(disableTextEdit);
    ui->tb_result6->setDisabled(disableTextEdit);
    ui->tb_result7->setDisabled(disableTextEdit);
    ui->tb_result8->setDisabled(disableTextEdit);
}

void Widget_TripleInputTruthTable::SetResults(bool results[])
{
    ui->tb_result1->setPlainText(results[0] ? "1" : "0");
    ui->tb_result2->setPlainText(results[1] ? "1" : "0");
    ui->tb_result3->setPlainText(results[2] ? "1" : "0");
    ui->tb_result4->setPlainText(results[3] ? "1" : "0");
    ui->tb_result5->setPlainText(results[4] ? "1" : "0");
    ui->tb_result6->setPlainText(results[5] ? "1" : "0");
    ui->tb_result7->setPlainText(results[6] ? "1" : "0");
    ui->tb_result8->setPlainText(results[7] ? "1" : "0");

    DisableTextEdit(true);
}

std::vector<bool> Widget_TripleInputTruthTable::GetResults()
{
    std::vector<bool> res;
    res.push_back(ui->tb_result1->toPlainText() == "1");
    res.push_back(ui->tb_result2->toPlainText() == "1");
    res.push_back(ui->tb_result3->toPlainText() == "1");
    res.push_back(ui->tb_result4->toPlainText() == "1");
    res.push_back(ui->tb_result5->toPlainText() == "1");
    res.push_back(ui->tb_result6->toPlainText() == "1");
    res.push_back(ui->tb_result7->toPlainText() == "1");
    res.push_back(ui->tb_result8->toPlainText() == "1");
    return res;
}

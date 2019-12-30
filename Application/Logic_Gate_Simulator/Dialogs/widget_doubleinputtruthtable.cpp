#include "widget_doubleinputtruthtable.h"
#include "ui_widget_doubleinputtruthtable.h"

Widget_DoubleInputTruthTable::Widget_DoubleInputTruthTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget_DoubleInputTruthTable)
{
    ui->setupUi(this);
}

Widget_DoubleInputTruthTable::~Widget_DoubleInputTruthTable()
{
    delete ui;
}

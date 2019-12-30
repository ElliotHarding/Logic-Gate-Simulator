#include "widget_tripleinputtruthtable.h"
#include "ui_widget_tripleinputtruthtable.h"

Widget_TripleInputTruthTable::Widget_TripleInputTruthTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget_TripleInputTruthTable)
{
    ui->setupUi(this);
}

Widget_TripleInputTruthTable::~Widget_TripleInputTruthTable()
{
    delete ui;
}

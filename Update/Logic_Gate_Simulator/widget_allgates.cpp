#include "widget_allgates.h"
#include "ui_widget_allgates.h"

Widget_AllGates::Widget_AllGates(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget_AllGates)
{
    ui->setupUi(this);
}

Widget_AllGates::~Widget_AllGates()
{
    delete ui;
}

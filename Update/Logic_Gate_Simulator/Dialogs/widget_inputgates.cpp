#include "widget_inputgates.h"
#include "ui_widget_inputgates.h"

Widget_InputGates::Widget_InputGates(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget_InputGates)
{
    ui->setupUi(this);
}

Widget_InputGates::~Widget_InputGates()
{
    delete ui;
}

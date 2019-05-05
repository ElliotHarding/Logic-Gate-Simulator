#include "widget_customgates.h"
#include "ui_widget_customgates.h"

Widget_CustomGates::Widget_CustomGates(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget_CustomGates)
{
    ui->setupUi(this);
}

Widget_CustomGates::~Widget_CustomGates()
{
    delete ui;
}

void Widget_CustomGates::on_Widget_CustomGates_destroyed()
{

}

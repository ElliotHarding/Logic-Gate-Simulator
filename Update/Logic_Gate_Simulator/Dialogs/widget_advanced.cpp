#include "widget_advanced.h"
#include "ui_widget_advanced.h"

Widget_Advanced::Widget_Advanced(QWidget *parent) :
    MovingWidget(parent),
    ui(new Ui::Widget_Advanced)
{
    ui->setupUi(this);
}

Widget_Advanced::~Widget_Advanced()
{
    delete ui;
}

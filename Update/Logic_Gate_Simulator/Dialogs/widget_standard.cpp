#include "widget_standard.h"
#include "ui_widget_standard.h"

Widget_Standard::Widget_Standard(QWidget *parent) :
    MovingWidget(parent),
    ui(new Ui::Widget_Standard)
{
    ui->setupUi(this);
}

Widget_Standard::~Widget_Standard()
{
    delete ui;
}

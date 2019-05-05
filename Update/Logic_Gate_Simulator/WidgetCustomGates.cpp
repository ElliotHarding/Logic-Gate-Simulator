#include "WidgetCustomGates.h"

WidgetCustomGates::WidgetCustomGates(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ui_WidgetCustomGates)
{
    ui->setupUi(this);
}

WidgetCustomGates::~WidgetCustomGates()
{
    delete ui;
}

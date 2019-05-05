#include "WidgetStandardGates.h"

WidgetStandardGates::WidgetStandardGates(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetStandardGates)
{
    ui->setupUi(this);
}

WidgetStandardGates::~WidgetStandardGates()
{
    delete ui;
}

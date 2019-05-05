#include "WidgetInputGates.h"

WidgetInputGates::WidgetInputGates(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetInputGates)
{
    ui->setupUi(this);
}

WidgetInputGates::~WidgetInputGates()
{
    delete ui;
}

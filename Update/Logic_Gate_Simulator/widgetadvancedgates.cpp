#include "WidgetAdvancedGates.h"

WidgetAdvancedGates::WidgetAdvancedGates(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetAdvancedGates)
{
    ui->setupUi(this);
}

WidgetAdvancedGates::~WidgetAdvancedGates()
{
    delete ui;
}

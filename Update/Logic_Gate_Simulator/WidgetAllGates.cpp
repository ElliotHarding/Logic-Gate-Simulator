#include "WidgetAllGates.h"

WidgetAllGates::WidgetAllGates(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetAllGates)
{
    ui->setupUi(this);
}

WidgetAllGates::~WidgetAllGates()
{
    delete ui;
}

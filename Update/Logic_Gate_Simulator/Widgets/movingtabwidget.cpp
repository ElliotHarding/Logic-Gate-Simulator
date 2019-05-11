#include "movingtabwidget.h"
#include "ui_movingtabwidget.h"

MovingTabWidget::MovingTabWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MovingTabWidget)
{
    ui->setupUi(this);
}

MovingTabWidget::~MovingTabWidget()
{
    delete ui;
}

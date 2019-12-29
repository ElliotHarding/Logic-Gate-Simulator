#include "widget_taskview.h"
#include "ui_widget_taskview.h"

widget_taskView::widget_taskView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget_taskView)
{
    ui->setupUi(this);
}

widget_taskView::~widget_taskView()
{
    delete ui;
}

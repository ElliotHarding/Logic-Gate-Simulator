#include "widget_helperpopup.h"
#include "ui_widget_helperpopup.h"

Widget_HelperPopup::Widget_HelperPopup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget_HelperPopup)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
}

Widget_HelperPopup::~Widget_HelperPopup()
{
    delete ui;
}

void Widget_HelperPopup::on_btn_close_clicked()
{

}


void Widget_HelperPopup::on_btn_next_clicked()
{

}


void Widget_HelperPopup::on_btn_previous_clicked()
{

}


#include "widget_advanced.h"
#include "ui_widget_advanced.h"
#include "dlg_home.h"

Widget_Advanced::Widget_Advanced(DLG_Home *parent) :
    MovingWidget(parent),
    ui(new Ui::Widget_Advanced)
{
    ui->setupUi(this);
}

Widget_Advanced::~Widget_Advanced()
{
    delete ui;
}

void Widget_Advanced::on_btn_numberOutputGate_clicked()
{
    if(m_pParent)
        m_pParent->AddGate(new GateNumberOutput());
}
void Widget_Advanced::on_btn_recieverGate_clicked()
{
    if(m_pParent)
        m_pParent->AddGate(new GateReciever());
}

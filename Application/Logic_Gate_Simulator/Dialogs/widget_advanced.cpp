#include "widget_advanced.h"
#include "ui_widget_advanced.h"
#include "dlg_home.h"

Widget_Advanced::Widget_Advanced(DLG_Home *parent, bool show, QPoint loc) :
    MovingWidget(parent, show, loc),
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
        m_pParent->AddGate(new GateNumberOutput(0, 0));
}
void Widget_Advanced::on_btn_recieverGate_clicked()
{
    if(m_pParent)
        m_pParent->AddGate(new GateReciever(0, 0));
}

//To be developed
//void Widget_Advanced::on_btn_fpgaGate_clicked()
//{
//    if(m_pParent)
//        m_pParent->AddGate(new GateFPGA());
//}

void Widget_Advanced::on_btn_labelGate_clicked()
{
    if(m_pParent)
        m_pParent->AddGate(new TextLabel(0, 0));
}

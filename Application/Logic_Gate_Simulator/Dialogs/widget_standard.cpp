#include "widget_standard.h"
#include "ui_widget_standard.h"
#include "dlg_home.h"

Widget_Standard::Widget_Standard(DLG_Home *parent, bool show, QPoint loc) :
    MovingWidget(parent, show, loc),
    ui(new Ui::Widget_Standard)
{
    ui->setupUi(this);
}

Widget_Standard::~Widget_Standard()
{
    delete ui;
}

void Widget_Standard::on_btn_orGate_clicked()
{
    if(m_pParent)
        m_pParent->AddGate(new GateOr(0,0));
}
void Widget_Standard::on_btn_notGate_clicked()
{
    if(m_pParent)
        m_pParent->AddGate(new GateNot(0,0));
}
void Widget_Standard::on_btn_andGate_clicked()
{
    if(m_pParent)
        m_pParent->AddGate(new GateAnd(0,0));
}
void Widget_Standard::on_btn_GateTriOr_clicked()
{
    if(m_pParent)
        m_pParent->AddGate(new GateTriOr(0,0));
}
void Widget_Standard::on_btn_GateTriAnd_clicked()
{
    if(m_pParent)
        m_pParent->AddGate(new GateTriAnd(0,0));
}

void Widget_Standard::on_btn_GateEor_clicked()
{
    if(m_pParent)
        m_pParent->AddGate(new GateEor(0,0));
}

void Widget_Standard::on_btn_GateTriEor_clicked()
{
    if(m_pParent)
        m_pParent->AddGate(new GateTriEor(0,0));
}

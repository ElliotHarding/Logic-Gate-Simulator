#include "widget_allgates.h"
#include "ui_widget_allgates.h"
#include "dlg_home.h"

Widget_AllGates::Widget_AllGates(DLG_Home* parent) :
    QWidget(parent),    
    ui(new Ui::Widget_AllGates),
    m_pParent(parent)
{
    ui->setupUi(this);
}
Widget_AllGates::~Widget_AllGates()
{
    delete ui;
}
void Widget_AllGates::on_btn_sourceGate_clicked()
{
    if(m_pParent)
        m_pParent->AddGate(new GateToggle());
}
void Widget_AllGates::on_btn_notGate_clicked()
{
    if(m_pParent)
        m_pParent->AddGate(new GateNot());
}
void Widget_AllGates::on_btn_orGate_clicked()
{
    if(m_pParent)
        m_pParent->AddGate(new GateOr());
}
void Widget_AllGates::on_btn_andGate_clicked()
{
    if(m_pParent)
        m_pParent->AddGate(new GateAnd());
}
void Widget_AllGates::on_btn_recieverGate_clicked()
{
    if(m_pParent)
        m_pParent->AddGate(new GateReciever());
}

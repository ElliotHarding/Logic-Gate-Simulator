#include "widget_inputgates.h"
#include "ui_widget_inputgates.h"
#include "dlg_home.h"

Widget_InputGates::Widget_InputGates(DLG_Home *parent) :
    MovingWidget(parent),
    ui(new Ui::Widget_InputGates)
{
    ui->setupUi(this);
}

Widget_InputGates::~Widget_InputGates()
{
    delete ui;
}
void Widget_InputGates::on_btn_sourceGate_clicked()
{
    if(m_pParent)
        m_pParent->AddGate(new GateToggle());
}
void Widget_InputGates::on_btn_inputOn_clicked()
{
    if(m_pParent)
        m_pParent->AddGate(new GateConstantActive());
}
void Widget_InputGates::on_btn_inputOff_clicked()
{
    if(m_pParent)
        m_pParent->AddGate(new GateConstantInactive());
}
void Widget_InputGates::on_btn_timerGate_clicked()
{
    if(m_pParent)
        m_pParent->AddGate(new GateTimer());
}

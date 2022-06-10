#include "widget_inputgates.h"
#include "ui_widget_inputgates.h"
#include "dlg_home.h"

Widget_InputGates::Widget_InputGates(DLG_Home *parent, bool show, QPoint loc) :
    MovingWidget(parent, show, loc),
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
        m_pParent->AddGate(new GateToggle(0, 0));
}
void Widget_InputGates::on_btn_inputOn_clicked()
{
    if(m_pParent)
        m_pParent->AddGate(new GateConstantActive(0, 0));
}
void Widget_InputGates::on_btn_inputOff_clicked()
{
    if(m_pParent)
        m_pParent->AddGate(new GateConstantInactive(0, 0));
}
void Widget_InputGates::on_btn_timerGate_clicked()
{
    if(m_pParent)
        m_pParent->AddGate(new GateTimer(0, 0));
}

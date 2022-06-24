#include "widget_inputgates.h"
#include "ui_widget_inputgates.h"
#include "dlg_home.h"
#include "GameObjects/GateToggle.h"
#include "GameObjects/GateConstantActive.h"
#include "GameObjects/GateConstantInactive.h"
#include "GameObjects/GateTimer.h"

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

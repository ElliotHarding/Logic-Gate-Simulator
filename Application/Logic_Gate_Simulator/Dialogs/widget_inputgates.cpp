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
    {
        const QPoint spawnPoint = spawnPosition(ui->btn_sourceGate->geometry().center());
        m_pParent->NewlySpawnedGate(new GateToggle(), spawnPoint);
    }
}
void Widget_InputGates::on_btn_inputOn_clicked()
{
    if(m_pParent)
    {
        const QPoint spawnPoint = spawnPosition(ui->btn_inputOn->geometry().center());
        m_pParent->NewlySpawnedGate(new GateConstantActive(), spawnPoint);
    }
}
void Widget_InputGates::on_btn_inputOff_clicked()
{
    if(m_pParent)
    {
        const QPoint spawnPoint = spawnPosition(ui->btn_inputOff->geometry().center());
        m_pParent->NewlySpawnedGate(new GateConstantInactive(), spawnPoint);
    }
}
void Widget_InputGates::on_btn_timerGate_clicked()
{
    if(m_pParent)
    {
        const QPoint spawnPoint = spawnPosition(ui->btn_timerGate->geometry().center());
        m_pParent->NewlySpawnedGate(new GateTimer(), spawnPoint);
    }
}

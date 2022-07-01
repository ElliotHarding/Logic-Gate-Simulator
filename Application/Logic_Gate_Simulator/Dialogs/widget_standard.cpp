#include "widget_standard.h"
#include "ui_widget_standard.h"
#include "dlg_home.h"
#include "allgates.h"

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
    {
        const QPoint spawnPoint = spawnPosition(ui->btn_orGate->geometry().center());
        m_pParent->NewlySpawnedGate(new GateOr(), spawnPoint);
    }
}
void Widget_Standard::on_btn_notGate_clicked()
{
    if(m_pParent)
    {
        const QPoint spawnPoint = spawnPosition(ui->btn_notGate->geometry().center());
        m_pParent->NewlySpawnedGate(new GateNot(), spawnPoint);
    }
}
void Widget_Standard::on_btn_andGate_clicked()
{
    if(m_pParent)
    {
        const QPoint spawnPoint = spawnPosition(ui->btn_andGate->geometry().center());
        m_pParent->NewlySpawnedGate(new GateAnd(), spawnPoint);
    }
}
void Widget_Standard::on_btn_GateTriOr_clicked()
{
    if(m_pParent)
    {
        const QPoint spawnPoint = spawnPosition(ui->btn_GateTriOr->geometry().center());
        m_pParent->NewlySpawnedGate(new GateTriOr(), spawnPoint);
    }
}
void Widget_Standard::on_btn_GateTriAnd_clicked()
{
    if(m_pParent)
    {
        const QPoint spawnPoint = spawnPosition(ui->btn_GateTriAnd->geometry().center());
        m_pParent->NewlySpawnedGate(new GateTriAnd(), spawnPoint);
    }
}

void Widget_Standard::on_btn_GateEor_clicked()
{
    if(m_pParent)
    {
        const QPoint spawnPoint = spawnPosition(ui->btn_GateEor->geometry().center());
        m_pParent->NewlySpawnedGate(new GateEor(), spawnPoint);
    }
}

void Widget_Standard::on_btn_GateTriEor_clicked()
{
    if(m_pParent)
    {
        const QPoint spawnPoint = spawnPosition(ui->btn_GateTriEor->geometry().center());
        m_pParent->NewlySpawnedGate(new GateTriEor(), spawnPoint);
    }
}

QPoint Widget_Standard::spawnPosition(const QPoint &buttonPoint) const
{
    return geometry().topLeft() + buttonPoint;
}

#include "widget_advanced.h"
#include "ui_widget_advanced.h"
#include "dlg_home.h"
#include "GameObjects/gatenumberoutput.h"
#include "GameObjects/GateReciever.h"
#include "GameObjects/gatefpga.h"
#include "GameObjects/textlabel.h"

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
    {
        const QPoint spawnPoint = spawnPosition(ui->btn_numberOutputGate->geometry().center());
        m_pParent->NewlySpawnedGate(new GateNumberOutput(), spawnPoint);
    }
}
void Widget_Advanced::on_btn_recieverGate_clicked()
{
    if(m_pParent)
    {
        const QPoint spawnPoint = spawnPosition(ui->btn_recieverGate->geometry().center());
        m_pParent->NewlySpawnedGate(new GateReciever(), spawnPoint);
    }
}

void Widget_Advanced::on_btn_fpgaGate_clicked()
{
    if(m_pParent)
    {
        const QPoint spawnPoint = spawnPosition(ui->btn_fpgaGate->geometry().center());
        m_pParent->NewlySpawnedGate(new GateFPGA(), spawnPoint);
    }
}

void Widget_Advanced::on_btn_labelGate_clicked()
{
    if(m_pParent)
    {
        const QPoint spawnPoint = spawnPosition(ui->btn_labelGate->geometry().center());
        m_pParent->NewlySpawnedGate(new TextLabel(), spawnPoint);
    }
}

QPoint Widget_Advanced::spawnPosition(const QPoint& buttonPoint) const
{
    return geometry().topLeft() + buttonPoint;
}

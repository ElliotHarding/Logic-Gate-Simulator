#include "widget_allgates.h"
#include "ui_widget_allgates.h"
#include "dlg_home.h"

Widget_AllGates::Widget_AllGates(DLG_Home* parent, bool show, QPoint loc) :
    MovingWidget(parent, show, loc),
    ui(new Ui::Widget_AllGates)
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
void Widget_AllGates::on_btn_timerGate_clicked()
{
    if(m_pParent)
        m_pParent->AddGate(new GateTimer());
}
void Widget_AllGates::on_btn_inputOn_clicked()
{
    if(m_pParent)
        m_pParent->AddGate(new GateConstantActive());
}
void Widget_AllGates::on_btn_inputOff_clicked()
{
    if(m_pParent)
        m_pParent->AddGate(new GateConstantInactive());
}

void Widget_AllGates::on_btn_GateTriAnd_clicked()
{
    if(m_pParent)
        m_pParent->AddGate(new GateTriAnd());
}

void Widget_AllGates::on_btn_GateTriOr_clicked()
{
    if(m_pParent)
        m_pParent->AddGate(new GateTriOr());
}

void Widget_AllGates::on_btn_numberOutputGate_clicked()
{
    if(m_pParent)
        m_pParent->AddGate(new GateNumberOutput());
}

void Widget_AllGates::on_btn_GateEor_clicked()
{
    if(m_pParent)
        m_pParent->AddGate(new GateEor());
}

void Widget_AllGates::on_btn_GateTriEor_clicked()
{
    if(m_pParent)
        m_pParent->AddGate(new GateTriEor());
}

void Widget_AllGates::SetupGateButtons()
{
    QWidget *widget = new QWidget();
    ui->m_scrollArea->setWidget( widget );

    QVBoxLayout *layout = new QVBoxLayout();
    widget->setLayout( layout );

    layout->addWidget( ui->btn_orGate );
    layout->addWidget( ui->btn_GateEor );
    layout->addWidget( ui->btn_andGate );
    layout->addWidget( ui->btn_inputOn );
    layout->addWidget( ui->btn_notGate );
    layout->addWidget( ui->btn_inputOff );
    layout->addWidget( ui->btn_GateTriOr );
    layout->addWidget( ui->btn_timerGate );
    layout->addWidget( ui->btn_GateTriAnd );
    layout->addWidget( ui->btn_sourceGate );
    layout->addWidget( ui->btn_recieverGate );
    layout->addWidget( ui->btn_numberOutputGate );

   // ui->scrollAreaWidgetContents->layout()->addWidget(ui->btn_orGate);
}

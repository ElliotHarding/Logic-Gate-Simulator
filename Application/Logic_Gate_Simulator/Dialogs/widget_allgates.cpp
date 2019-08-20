#include "widget_allgates.h"
#include "ui_widget_allgates.h"
#include "dlg_home.h"
#include "simpleslider.h"

Widget_AllGates::Widget_AllGates(DLG_Home* parent, bool show, QPoint loc) :
    MovingWidget(parent, show, loc),
    ui(new Ui::Widget_AllGates)
{
    ui->setupUi(this);

    //save layout
    QRect layout = ui->scrollSliderLayout->geometry();
    ui->scrollSliderLayout = new GateSlider(1, 100, this, Qt::black);

    //set layout after construction
    dynamic_cast<VerticalSimpleSlider*>(ui->scrollSliderLayout)->SetGeometry(layout);
    ui->scrollSliderLayout->raise();

    m_buttons.push_back({ui->btn_orGate, ui->btn_orGate->geometry()});
    m_buttons.push_back({ui->btn_GateEor, ui->btn_GateEor->geometry()});
    m_buttons.push_back({ui->btn_andGate, ui->btn_andGate->geometry()});
    m_buttons.push_back({ui->btn_inputOn, ui->btn_inputOn->geometry()});
    m_buttons.push_back({ui->btn_notGate, ui->btn_notGate->geometry()});
    m_buttons.push_back({ui->btn_inputOff, ui->btn_inputOff->geometry()});
    m_buttons.push_back({ui->btn_GateTriOr, ui->btn_GateTriOr->geometry()});
    m_buttons.push_back({ui->btn_timerGate, ui->btn_timerGate->geometry()});
    m_buttons.push_back({ui->btn_GateTriAnd, ui->btn_GateTriAnd->geometry()});
    m_buttons.push_back({ui->btn_GateTriEor, ui->btn_GateTriEor->geometry()});
    m_buttons.push_back({ui->btn_sourceGate, ui->btn_sourceGate->geometry()});
    m_buttons.push_back({ui->btn_recieverGate, ui->btn_recieverGate->geometry()});
    m_buttons.push_back({ui->btn_numberOutputGate, ui->btn_numberOutputGate->geometry()});
    m_buttons.push_back({ui->ln_1, ui->ln_1->geometry()});
    m_buttons.push_back({ui->ln_2, ui->ln_2->geometry()});

    dynamic_cast<VerticalSimpleSlider*>(ui->scrollSliderLayout)->SetValue(0);
    //SetScrollPosition(0);
}
Widget_AllGates::~Widget_AllGates()
{
    delete ui;
}

void Widget_AllGates::SetScrollPosition(float y)
{
    int scroll = y + 100;

    for (WidgetAndPosition widget : m_buttons)
    {
        const int newTop = widget.originalLayout.top() - scroll;
        const QRect scrolledLayout = QRect(widget.originalLayout.left(), (newTop > 1) ? newTop : 1, widget.originalLayout.width(), widget.originalLayout.height());
        widget.widget->setGeometry(scrolledLayout);
    }
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

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
    delete ui->scrollSliderLayout;
    ui->scrollSliderLayout = new GateSlider(this, layout, c_scrollMin, c_scrollMax, 0);
    ui->scrollSliderLayout->raise();

    m_scroll = c_scrollMin;
    SetScrollPosition(c_scrollMin);
    dynamic_cast<VerticalSimpleSlider*>(ui->scrollSliderLayout)->SetValue(c_scrollMin);
}

Widget_AllGates::~Widget_AllGates()
{
    delete ui;
}

void Widget_AllGates::SetScrollPosition(const float& y)
{
    const int diff = y - m_scroll;
    m_scroll += diff;

    applyScrollDiff(-diff);
}

void Widget_AllGates::wheelEvent(QWheelEvent *event)
{
    //Apply scroll delta to m_scroll
    const int direction = event->delta() > 0 ? -c_scrollSpeed : c_scrollSpeed;
    int newScroll = m_scroll + direction;

    //Make sure m_scroll is between c_scrollMin & c_scrollMax
    if (newScroll > c_scrollMax)
        newScroll = c_scrollMax;
    else if (newScroll < c_scrollMin)
        newScroll = c_scrollMin;

    //Update
    SetScrollPosition(newScroll);
    dynamic_cast<VerticalSimpleSlider*>(ui->scrollSliderLayout)->SetValue(newScroll);
}

void Widget_AllGates::applyScrollDiff(const int& diff)
{
    for(QWidget* pWidget : findChildren<QWidget*>())
    {
        if(pWidget == ui->scrollSliderLayout)
            continue;

        const int newTop = pWidget->geometry().top() + diff;
        if(newTop < 7)
            pWidget->hide();
        else
            pWidget->show();

        pWidget->setGeometry(pWidget->geometry().translated(0, diff));
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

void Widget_AllGates::on_btn_labelGate_clicked()
{
    if(m_pParent)
        m_pParent->AddGate(new TextLabel());
}

void Widget_AllGates::on_btn_norGate_clicked()
{
    if(m_pParent)
        m_pParent->AddGate(new GateNor());
}

void Widget_AllGates::on_btn_nandGate_clicked()
{
    if(m_pParent)
        m_pParent->AddGate(new GateNand());
}

void Widget_AllGates::on_btn_xorGate_clicked()
{
    if(m_pParent)
        m_pParent->AddGate(new GateXor());
}

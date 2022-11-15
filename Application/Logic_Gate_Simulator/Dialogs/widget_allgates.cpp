#include "widget_allgates.h"
#include "ui_widget_allgates.h"
#include "dlg_home.h"
#include "simpleslider.h"
#include "allgates.h"

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
    setScrollPosition(c_scrollMin);
    dynamic_cast<VerticalSimpleSlider*>(ui->scrollSliderLayout)->setValue(c_scrollMin);
}

Widget_AllGates::~Widget_AllGates()
{
    delete ui;
}

void Widget_AllGates::setScrollPosition(const float& y)
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
    setScrollPosition(newScroll);
    dynamic_cast<VerticalSimpleSlider*>(ui->scrollSliderLayout)->setValue(newScroll);
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
    {
        const QPoint spawnPoint = spawnPosition(ui->btn_sourceGate->geometry().center());
        m_pParent->newlySpawnedGate(new GateToggle(), spawnPoint);
    }
}
void Widget_AllGates::on_btn_notGate_clicked()
{
    if(m_pParent)
    {
        const QPoint spawnPoint = spawnPosition(ui->btn_notGate->geometry().center());
        m_pParent->newlySpawnedGate(new GateNot(), spawnPoint);
    }
}
void Widget_AllGates::on_btn_orGate_clicked()
{
    if(m_pParent)
    {
        const QPoint spawnPoint = spawnPosition(ui->btn_orGate->geometry().center());
        m_pParent->newlySpawnedGate(new GateOr(), spawnPoint);
    }
}
void Widget_AllGates::on_btn_andGate_clicked()
{
    if(m_pParent)
    {
        const QPoint spawnPoint = spawnPosition(ui->btn_andGate->geometry().center());
        m_pParent->newlySpawnedGate(new GateAnd(), spawnPoint);
    }
}
void Widget_AllGates::on_btn_recieverGate_clicked()
{
    if(m_pParent)
    {
        const QPoint spawnPoint = spawnPosition(ui->btn_recieverGate->geometry().center());
        m_pParent->newlySpawnedGate(new GateReciever(), spawnPoint);
    }
}
void Widget_AllGates::on_btn_timerGate_clicked()
{
    if(m_pParent)
    {
        const QPoint spawnPoint = spawnPosition(ui->btn_timerGate->geometry().center());
        m_pParent->newlySpawnedGate(new GateTimer(), spawnPoint);
    }
}
void Widget_AllGates::on_btn_inputOn_clicked()
{
    if(m_pParent)
    {
        const QPoint spawnPoint = spawnPosition(ui->btn_inputOn->geometry().center());
        m_pParent->newlySpawnedGate(new GateConstantActive(), spawnPoint);
    }
}
void Widget_AllGates::on_btn_inputOff_clicked()
{
    if(m_pParent)
    {
        const QPoint spawnPoint = spawnPosition(ui->btn_inputOff->geometry().center());
        m_pParent->newlySpawnedGate(new GateConstantInactive(), spawnPoint);
    }
}

void Widget_AllGates::on_btn_GateTriAnd_clicked()
{
    if(m_pParent)
    {
        const QPoint spawnPoint = spawnPosition(ui->btn_GateTriAnd->geometry().center());
        m_pParent->newlySpawnedGate(new GateTriAnd(), spawnPoint);
    }
}

void Widget_AllGates::on_btn_GateTriOr_clicked()
{
    if(m_pParent)
    {
        const QPoint spawnPoint = spawnPosition(ui->btn_GateTriOr->geometry().center());
        m_pParent->newlySpawnedGate(new GateTriOr(), spawnPoint);
    }
}

void Widget_AllGates::on_btn_numberOutputGate_clicked()
{
    if(m_pParent)
    {
        const QPoint spawnPoint = spawnPosition(ui->btn_numberOutputGate->geometry().center());
        m_pParent->newlySpawnedGate(new GateNumberOutput(), spawnPoint);
    }
}

void Widget_AllGates::on_btn_GateEor_clicked()
{
    if(m_pParent)
    {
        const QPoint spawnPoint = spawnPosition(ui->btn_GateEor->geometry().center());
        m_pParent->newlySpawnedGate(new GateEor(), spawnPoint);
    }
}

void Widget_AllGates::on_btn_GateTriEor_clicked()
{
    if(m_pParent)
    {
        const QPoint spawnPoint = spawnPosition(ui->btn_GateTriEor->geometry().center());
        m_pParent->newlySpawnedGate(new GateTriEor(), spawnPoint);
    }
}

void Widget_AllGates::on_btn_labelGate_clicked()
{
    if(m_pParent)
    {
        const QPoint spawnPoint = spawnPosition(ui->btn_labelGate->geometry().center());
        m_pParent->newlySpawnedGate(new TextLabel(), spawnPoint);
    }
}

void Widget_AllGates::on_btn_norGate_clicked()
{
    if(m_pParent)
    {
        const QPoint spawnPoint = spawnPosition(ui->btn_norGate->geometry().center());
        m_pParent->newlySpawnedGate(new GateNor(), spawnPoint);
    }
}

void Widget_AllGates::on_btn_nandGate_clicked()
{
    if(m_pParent)
    {
        const QPoint spawnPoint = spawnPosition(ui->btn_nandGate->geometry().center());
        m_pParent->newlySpawnedGate(new GateNand(), spawnPoint);
    }
}

void Widget_AllGates::on_btn_xorGate_clicked()
{
    if(m_pParent)
    {
        const QPoint spawnPoint = spawnPosition(ui->btn_xorGate->geometry().center());
        m_pParent->newlySpawnedGate(new GateXor(), spawnPoint);
    }
}

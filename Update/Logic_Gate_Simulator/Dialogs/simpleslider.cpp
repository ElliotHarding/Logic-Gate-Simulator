#include "simpleslider.h"
#include <QMouseEvent>
#include <QPainter>
#include "dlg_home.h"

SimpleSlider::SimpleSlider(float min, float max, QPoint pos, int size, DLG_Home* parent) :
    QWidget(parent),
    m_max(max),
    m_min(min),
    m_size(size),
    m_pParent(parent),
    m_beingClicked(false),
    m_minMaxDiff(max - min)
{
    m_rightMost = QPoint(m_size + c_margin, c_height/2);
    m_leftMost = QPoint(c_margin, c_height/2);
    m_sliderPosition = m_leftMost;

    this->setGeometry(pos.x(), pos.y(), m_size + (c_margin * 2), c_height);

    setAcceptDrops(true);
    setMouseTracking(true);
}

float SimpleSlider::GetCurrentValue()
{
    //Get how far slider is in terms of percentage from left
    float distanceFromLeft = (m_sliderPosition.x() - m_leftMost.x());
    float percentage = distanceFromLeft / m_size;

    //Apply same percentage across min - max difference
    return m_min + (m_minMaxDiff * percentage);
}

void SimpleSlider::mouseReleaseEvent(QMouseEvent *releaseEvent)
{
    m_beingClicked = false;
}

void SimpleSlider::mousePressEvent(QMouseEvent *mouseEvent)
{
    m_beingClicked = true;

    UpdateSlider(mouseEvent->pos().x());
}

void SimpleSlider::mouseMoveEvent(QMouseEvent *event)
{
    UpdateSlider(event->pos().x());
}

void SimpleSlider::paintEvent(QPaintEvent *paintEvent)
{
    QPainter painter(this);

    //Paiting variables to be used
    QPainterPath path;
    QPen pen(Qt::white, 6);
    painter.setPen(pen);

    //Draw bar
    painter.drawLine(m_leftMost, m_rightMost);

    //Set slider colour
    pen.setColor(m_beingClicked ? Qt::lightGray : Qt::darkGray);
    painter.setPen(pen);

    //Draw slider
    painter.drawEllipse(m_sliderPosition, 5, 5);
}

void SimpleSlider::UpdateSlider(int currentMousePosX)
{
    if(!m_beingClicked)
        return;

    //Check if mouse inbetween leftMost & rightMost boundaries of slider
    //If so move m_sliderPosition corredspondingly
    if(m_leftMost.x() < currentMousePosX && currentMousePosX < m_rightMost.x())
    {
        m_sliderPosition.setX(currentMousePosX);

        //Send new data
        m_pParent->SetZoomFactor(GetCurrentValue());

        //Redraw
        update();
    }
}

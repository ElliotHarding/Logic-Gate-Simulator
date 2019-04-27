#include "simpleslider.h"
#include <QMouseEvent>
#include <QPainter>

SimpleSlider::SimpleSlider(float min, float max, QPoint pos, int size, QWidget *parent) :
    QWidget(parent),
    m_beingClicked(false),
    m_size(size),
    m_max(max),
    m_min(min),
    m_minMaxDiff(max - min),
    m_sliderPosition(pos)
{
    m_rightMost = QPoint(pos.x() + (m_size/2), pos.y());
    m_leftMost = QPoint(pos.x() - (m_size/2), pos.y());

    setAcceptDrops(true);
    setMouseTracking(true);
}

float SimpleSlider::GetCurrentValue()
{
    //Get how far slider is in terms of percentage from left
    float percentage = m_sliderPosition.x() / m_size;

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
}

void SimpleSlider::mouseMoveEvent(QMouseEvent *event)
{
    if(!m_beingClicked)
        return;

    const int currentMousePosX = event->pos().x();

    //Check if mouse inbetween leftMost & rightMost boundaries of slider
    //If so move m_sliderPosition corredspondingly
    if(m_leftMost.x() < currentMousePosX && currentMousePosX < m_rightMost.x())
    {
        if(currentMousePosX > m_sliderPosition.x())
        {
            m_sliderPosition.setX(m_sliderPosition.x() + 1);
            //Redraw
            update();
        }
        else if(currentMousePosX < m_sliderPosition.x())
        {
            m_sliderPosition.setX(m_sliderPosition.x() - 1);
            //Redraw
            update();
        }
    }
}

void SimpleSlider::paintEvent(QPaintEvent *paintEvent)
{
    QPainter painter(this);

    //Paiting variables to be used
    QPainterPath path;
    QPen pen(Qt::blue, 10);
    painter.setPen(pen);

    //Draw bar
    painter.drawLine(m_leftMost, m_rightMost);

    //Set slider colour
    pen.setColor(m_beingClicked ? Qt::lightGray : Qt::darkGray);
    painter.setPen(pen);

    //Draw slider
    painter.drawEllipse(m_sliderPosition, 5, 5);
}

#include "simpleslider.h"
#include <QMouseEvent>
#include <QPainter>

SimpleSlider::SimpleSlider(float min, float max, QPoint pos, int size, float incSize, QWidget *parent) :
    QWidget(parent),
    m_beingClicked(false),
    m_size(size),
    m_max(max),
    m_min(min),
    m_incrementSize(incSize),
    m_position(pos)
{
    m_minMaxDiff = max - min;
    m_currentValue = (m_minMaxDiff / 2) + min;

    setAcceptDrops(true);
    setMouseTracking(true);
}

void SimpleSlider::mouseReleaseEvent(QMouseEvent *releaseEvent)
{
    m_beingClicked = false;
}

void SimpleSlider::mousePressEvent(QMouseEvent *mouseEvent)
{
    m_beingClicked = true;
    m_currentMousePosX = mouseEvent->pos().x();
}

void SimpleSlider::mouseMoveEvent(QMouseEvent *event)
{
    if(!m_beingClicked)
        return;

    const int previousMousePosX = m_currentMousePosX;
    m_currentMousePosX = event->pos().x();

    if(previousMousePosX > m_currentMousePosX)
    {
        if(m_currentValue < m_max)
        {
            m_currentValue += m_incrementSize;

            //Redraw
            update();
        }
    }

    else if(previousMousePosX < m_currentMousePosX)
    {
        if(m_currentValue > m_min)
        {
            m_currentValue -= m_incrementSize;

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

    //Calculate bar position
    QPoint leftMost(m_position);
    QPoint rightMost(m_position);
    rightMost.setX(leftMost.x() + (m_size/2));
    leftMost.setX(leftMost.x() - (m_size/2));

    //Draw bar
    painter.drawLine(leftMost, rightMost);

    //Calculate slider position
    const float gainedFromMin = m_currentValue - m_min;
    const float percentageGainedFromMin = gainedFromMin/m_minMaxDiff;
    float xPos = leftMost.x() + (m_size * percentageGainedFromMin);
    QPoint sliderPos(xPos,m_position.y());

    //Set slider colour
    pen.setColor(m_beingClicked ? Qt::lightGray : Qt::darkGray);
    painter.setPen(pen);

    //Draw slider
    painter.drawEllipse(sliderPos, 5, 5);
}

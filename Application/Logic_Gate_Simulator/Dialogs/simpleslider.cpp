#include "simpleslider.h"
#include <QMouseEvent>
#include <QPainter>
#include "dlg_home.h"

SimpleSlider::SimpleSlider(float min, float max, QRect layout, DLG_Home *parent) :
    QWidget(parent),
    m_max(max),
    m_min(min),
    m_width(layout.width() - (c_margin * 2)),
    m_pParent(parent),
    m_beingClicked(false),
    m_minMaxDiff(max - min)
{
    m_rightMost = QPoint(m_width + c_margin, c_height/2);
    m_leftMost = QPoint(c_margin, c_height/2);
    m_sliderPosition = m_leftMost;

    this->setGeometry(layout.left(), layout.top(), layout.width(), c_height);

    setAcceptDrops(true);
    setMouseTracking(true);
}

float SimpleSlider::GetCurrentValue()
{
    //Get how far slider is in terms of percentage from left
    float distanceFromLeft = (m_sliderPosition.x() - m_leftMost.x());
    float percentage = distanceFromLeft / m_width;

    //Apply same percentage across min - max difference
    return m_min + (m_minMaxDiff * percentage);
}

void SimpleSlider::SetValue(float val)
{
    //Calculate position from value
    const float length = (m_rightMost.x() - m_leftMost.x());
    const float unit = length/m_minMaxDiff;
    const float distanceFromLeft = val * unit;
    float pos = m_leftMost.x() + distanceFromLeft - 5;

    SetSliderPosition(pos);
}


void SimpleSlider::mouseReleaseEvent(QMouseEvent *releaseEvent)
{
    m_beingClicked = false;
    update();
}

void SimpleSlider::mousePressEvent(QMouseEvent *mouseEvent)
{
    m_beingClicked = true;

    UpdateSlider(mouseEvent->pos().x());
}

void SimpleSlider::mouseMoveEvent(QMouseEvent *event)
{
    if(m_beingClicked)
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

    //Set slider colourSetZoomFactor);
    painter.setPen(pen);

    //Draw slider
    painter.drawEllipse(m_sliderPosition, 5, 5);
}

void SimpleSlider::UpdateSlider(float currentMousePosX)
{
    SetSliderPosition(currentMousePosX);

    //Send new data
    m_pParent->SetZoomFactor(GetCurrentValue(), false);
}

void SimpleSlider::SetSliderPosition(float val)
{
    //Check if mouse inbetween leftMost & rightMost boundaries of slider
    if(m_leftMost.x() > val)
        val = m_leftMost.x();

    else if(m_rightMost.x() < val)
        val = m_rightMost.x();

    m_sliderPosition.setX(val);

    //Redraw
    update();
}

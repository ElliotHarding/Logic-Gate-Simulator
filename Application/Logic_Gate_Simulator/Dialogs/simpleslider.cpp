#include "simpleslider.h"
#include <QMouseEvent>
#include <QPainter>
#include "dlg_home.h"
#include "dlg_textedit.h"

SimpleSlider::SimpleSlider(QWidget* pParent, float min, float max, QRect layout) :
    QWidget(pParent),
    m_max(max),
    m_min(min),
    m_width(layout.width() - (c_margin * 2)),
    m_beingClicked(false),
    m_minMaxDiff(max - min)
{
    this->setGeometry(layout);

    //Calculate positions
    m_rightMost = QPoint(layout.width() - c_margin * 2, layout.height()/2);
    m_leftMost = QPoint(c_margin, layout.height()/2);
    m_sliderPosition = m_leftMost;

    //setAcceptDrops(true);
    //setMouseTracking(true);
}

SimpleSlider::~SimpleSlider()
{
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
    const float lenghtPerUnit = length/m_minMaxDiff;
    const qreal distanceFromLeft = val * lenghtPerUnit;
    float pos = m_leftMost.x() + distanceFromLeft - c_margin;

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
    UpdateParent(GetCurrentValue());
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



//
//  FontSlider : SimpleSlider
//

FontSlider::FontSlider(float min, float max, QRect layout, DLG_TextEdit *parent) :
    SimpleSlider (parent, min, max, layout),
    m_pParent(parent)
{
}

FontSlider::~FontSlider()
{
    m_pParent = nullptr;
}

void FontSlider::UpdateParent(float val)
{
    //Send new data
    m_pParent->SetFontSize(val);
}



//
//  ZoomSlider : SimpleSlider
//

ZoomSlider::ZoomSlider(float min, float max, QRect layout, DLG_Home *parent) :
    SimpleSlider (parent, min, max, layout),
    m_pParent(parent)
{
}

ZoomSlider::~ZoomSlider()
{
    m_pParent = nullptr;
}

void ZoomSlider::UpdateParent(float val)
{
    m_pParent->SetZoomFactor(val, false);
}

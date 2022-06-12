#include "simpleslider.h"
#include <QMouseEvent>
#include <QPainter>
#include "dlg_home.h"
#include "dlg_textedit.h"

namespace Settings
{
const uint SliderNubSize = 10;
const uint SliderDrawHeight = 6;
}

SimpleSlider::SimpleSlider(QWidget* pParent, const QRect& layout, const float& min, const float& max, const uint& scrollSpeed, const QColor& sliderCol, const QColor& nubbleCol) :
    QWidget(pParent),
    m_sliderCol(sliderCol),
    m_nubbleCol(nubbleCol),
    m_scrollSpeed(scrollSpeed),
    m_beingClicked(false),
    m_max(max),
    m_min(min),
    m_minMaxDiff(max - min)
{
    setGeometry(layout);

    //Calculate positions & dimensions
    m_length = geometry().width() - (c_margin * 2);

    m_minPoint = QPoint(c_margin, geometry().height()/2);
    m_maxPoint = QPoint(m_minPoint.x() + m_length, geometry().height()/2);

    m_sliderPosition = m_minPoint;
}

SimpleSlider::~SimpleSlider()
{
}

float SimpleSlider::GetCurrentValue() const
{
    const float distanceFromLeft = (m_sliderPosition.x() - m_minPoint.x());
    const float percentage = distanceFromLeft / m_length;
    return m_min + (m_minMaxDiff * percentage);
}

void SimpleSlider::SetValue(const float& val)
{
    //Calculate position from value
    const float lenghtPerUnit = m_length/m_minMaxDiff;
    const qreal distanceFromLeft = val * lenghtPerUnit;
    float pos = m_minPoint.x() + distanceFromLeft - (c_margin * 2 + Settings::SliderNubSize/2);

    SetSliderPosition(pos);
}

void SimpleSlider::mouseReleaseEvent(QMouseEvent*)
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

void SimpleSlider::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    //Paiting variables to be used
    QPainterPath path;
    QPen pen(m_sliderCol, Settings::SliderDrawHeight);
    painter.setPen(pen);

    //Draw bar
    painter.drawLine(m_minPoint, m_maxPoint);

    //Set slider colourSetZoomFactor
    pen.setColor(Qt::darkGray);
    painter.setPen(pen);

    //Draw slider
    painter.drawLine(QPoint(m_sliderPosition.x() + Settings::SliderNubSize, m_minPoint.y()), QPoint(m_sliderPosition.x() - Settings::SliderNubSize, m_minPoint.y()));
}

void SimpleSlider::wheelEvent(QWheelEvent *event)
{
    const int direction = event->delta() > 0 ? m_scrollSpeed : -m_scrollSpeed;

    UpdateSlider(m_sliderPosition.x() + direction);
}

void SimpleSlider::UpdateSlider(const float& currentMousePos)
{
    SetSliderPosition(currentMousePos);

    //Send new data
    UpdateParent(GetCurrentValue());
}

void SimpleSlider::SetSliderPosition(float val)
{
    //Check if mouse inbetween leftMost & rightMost boundaries of slider
    if(m_minPoint.x() > val)
        val = m_minPoint.x();

    else if(m_maxPoint.x() < val)
        val = m_maxPoint.x();

    m_sliderPosition.setX(val);

    //Redraw
    update();
}



//
//  FontSlider : SimpleSlider
//

FontSlider::FontSlider(DLG_TextEdit* parent, const QRect& layout, const float& min, const float& max, const uint& scrollSpeed) :
    SimpleSlider(parent, layout, min, max, scrollSpeed),
    m_pParent(parent)
{
}

FontSlider::~FontSlider()
{
}

void FontSlider::UpdateParent(const float& val)
{
    m_pParent->SetFontSize(val);
}



//
//  ZoomSlider : SimpleSlider
//

ZoomSlider::ZoomSlider(DLG_Home* parent, const QRect& layout, const float& min, const float& max, const uint& scrollSpeed) :
    SimpleSlider (parent, layout, min, max, scrollSpeed),
    m_pParent(parent)
{
}

ZoomSlider::~ZoomSlider()
{
}

void ZoomSlider::UpdateParent(const float& val)
{
    m_pParent->SetZoomFactor(val, false);
}


//
//  GateSlider : VerticalSimpleSlider
//

GateSlider::GateSlider(Widget_AllGates* parent, const QRect& layout, const float& min, const float& max, const uint& scrollSpeed) :
    VerticalSimpleSlider (parent, layout, min, max, scrollSpeed),
    m_pParent(parent)
{
}

GateSlider::~GateSlider()
{
    m_pParent = nullptr;
}

void GateSlider::UpdateParent(const float& val)
{
    m_pParent->SetScrollPosition(val);
}


//
//  VerticalSimpleSlider : SimpleSlider
//

VerticalSimpleSlider::VerticalSimpleSlider(QWidget *pParent, const QRect& layout, const float& min, const float& max, const uint& scrollSpeed) :
    SimpleSlider (pParent, layout, min, max, scrollSpeed)
{
    //Calculate positions & dimensions
    m_length = layout.height() - (c_margin * 2);

    m_minPoint = QPoint(layout.width()/2, layout.bottom() - c_margin);
    m_maxPoint = QPoint(layout.width()/2, layout.top() + c_margin);

    m_sliderPosition = m_minPoint;
}

void VerticalSimpleSlider::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    //Paiting variables to be used
    QPainterPath path;
    QPen pen(m_sliderCol, 6);
    painter.setPen(pen);

    //Draw bar
    painter.drawLine(m_minPoint, m_maxPoint);

    //Set slider colourSetZoomFactor
    pen.setColor(Qt::darkGray);
    painter.setPen(pen);

    //Draw slider
    painter.drawLine(QPoint(m_minPoint.x(), m_sliderPosition.y() + 5), QPoint(m_minPoint.x(), m_sliderPosition.y() - 5));
}

void VerticalSimpleSlider::SetSliderPosition(float val)
{
    //Check if mouse inbetween leftMost & rightMost boundaries of slider
    if(m_minPoint.y() < val)
        val = m_minPoint.y();

    else if(m_maxPoint.y() > val)
        val = m_maxPoint.y();

    m_sliderPosition.setY(val);

    //Redraw
    update();
}

void VerticalSimpleSlider::mousePressEvent(QMouseEvent *mouseEvent)
{
    m_beingClicked = true;

    UpdateSlider(mouseEvent->pos().y());
}

void VerticalSimpleSlider::mouseMoveEvent(QMouseEvent *event)
{
    if(m_beingClicked)
        UpdateSlider(event->pos().y());
}

float VerticalSimpleSlider::GetCurrentValue() const
{
    //Get how far slider is in terms of percentage from left
    float distanceFromTop = (m_minPoint.y() - m_sliderPosition.y());
    float percentage = distanceFromTop / m_length;

    //Apply same percentage across min - max difference
    return m_min + (m_minMaxDiff * percentage);
}

void VerticalSimpleSlider::SetValue(const float& val)
{
    //Calculate position from value
    const float lenghtPerUnit = m_length/m_minMaxDiff;
    const qreal distanceFromTop = val * lenghtPerUnit;
    float pos = m_maxPoint.y() + distanceFromTop;

    SetSliderPosition(pos);
}


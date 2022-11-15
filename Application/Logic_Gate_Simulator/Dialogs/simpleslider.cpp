#include "simpleslider.h"
#include <QMouseEvent>
#include <QPainter>
#include "dlg_home.h"
#include "dlg_textedit.h"

namespace Settings
{
const uint SliderNubSize = 10;
const uint HalfSliderNubSize = SliderNubSize/2;
const uint SliderMargins = 10;
const uint SliderDrawThickness = 6;
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

    m_minDrawPoint = QPoint(Settings::SliderMargins, geometry().height()/2);
    m_maxDrawPoint = QPoint(geometry().width() - Settings::SliderMargins, geometry().height()/2);

    m_minPoint = m_minDrawPoint.x() + Settings::HalfSliderNubSize;
    m_maxPoint = m_maxDrawPoint.x() - Settings::HalfSliderNubSize;

    m_length = m_maxPoint - m_minPoint;

    m_sliderPosition = QPoint(m_minPoint, m_minDrawPoint.y());
}

SimpleSlider::~SimpleSlider()
{
}

float SimpleSlider::getCurrentValue() const
{
    const float distanceFromLeft = (m_sliderPosition.x() - m_minPoint);
    const float percentage = distanceFromLeft / m_length;
    return m_min + (m_minMaxDiff * percentage);
}

void SimpleSlider::setValue(const float& val)
{
    //Calculate position from value
    const float lenghtPerUnit = m_length/m_minMaxDiff;
    const qreal distanceFromLeft = val * lenghtPerUnit;
    float pos = m_minPoint + distanceFromLeft;

    setSliderPosition(pos);
}

void SimpleSlider::mouseReleaseEvent(QMouseEvent*)
{
    m_beingClicked = false;
    update();
}

void SimpleSlider::mousePressEvent(QMouseEvent *mouseEvent)
{
    m_beingClicked = true;
    updateSlider(mouseEvent->pos().x());
}

void SimpleSlider::mouseMoveEvent(QMouseEvent *event)
{
    if(m_beingClicked)
        updateSlider(event->pos().x());
}

void SimpleSlider::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    //Paiting variables to be used
    QPen pen(m_sliderCol, Settings::SliderDrawThickness);
    painter.setPen(pen);

    //Draw bar
    painter.drawLine(m_minDrawPoint, m_maxDrawPoint);

    //Set slider coloursetZoomFactor
    pen.setColor(m_nubbleCol);
    painter.setPen(pen);

    //Draw slider
    painter.drawLine(QPoint(m_sliderPosition.x() + Settings::HalfSliderNubSize, m_minDrawPoint.y()), QPoint(m_sliderPosition.x() - Settings::HalfSliderNubSize, m_maxDrawPoint.y()));
}

void SimpleSlider::wheelEvent(QWheelEvent *event)
{
    const int direction = event->delta() > 0 ? m_scrollSpeed : -m_scrollSpeed;

    updateSlider(m_sliderPosition.x() + direction);
}

void SimpleSlider::updateSlider(const float& currentMousePos)
{
    setSliderPosition(currentMousePos);

    //Send new data
    updateParent(getCurrentValue());
}

void SimpleSlider::setSliderPosition(float val)
{
    //Check if mouse inbetween leftMost & rightMost boundaries of slider
    if(m_minPoint > val)
        val = m_minPoint;

    else if(m_maxPoint < val)
        val = m_maxPoint;

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

void FontSlider::updateParent(const float& val)
{
    m_pParent->setFontSize(val);
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

void ZoomSlider::updateParent(const float& val)
{
    m_pParent->setZoomFactor(val, false);
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

void GateSlider::updateParent(const float& val)
{
    m_pParent->setScrollPosition(val);
}


//
//  VerticalSimpleSlider : SimpleSlider
//

VerticalSimpleSlider::VerticalSimpleSlider(QWidget *pParent, const QRect& layout, const float& min, const float& max, const uint& scrollSpeed) :
    SimpleSlider (pParent, layout, min, max, scrollSpeed)
{
    m_minDrawPoint = QPoint(layout.width()/2, Settings::SliderMargins);
    m_maxDrawPoint = QPoint(layout.width()/2, layout.height() - Settings::SliderMargins);

    m_minPoint = m_minDrawPoint.y() + Settings::HalfSliderNubSize;
    m_maxPoint = m_maxDrawPoint.y() - Settings::HalfSliderNubSize;

    m_length = m_maxPoint - m_minPoint;

    m_sliderPosition = QPoint(m_minDrawPoint.x(), m_minPoint);
}

void VerticalSimpleSlider::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    //Paiting variables to be used
    QPen pen(m_sliderCol, Settings::SliderDrawThickness);
    painter.setPen(pen);

    //Draw bar
    painter.drawLine(m_minDrawPoint, m_maxDrawPoint);

    //Set slider coloursetZoomFactor
    pen.setColor(m_nubbleCol);
    painter.setPen(pen);

    //Draw slider
    painter.drawLine(QPoint(m_minDrawPoint.x(), m_sliderPosition.y() + Settings::HalfSliderNubSize), QPoint(m_minDrawPoint.x(), m_sliderPosition.y() - Settings::HalfSliderNubSize));
}

void VerticalSimpleSlider::setSliderPosition(float val)
{
    //Check if mouse inbetween leftMost & rightMost boundaries of slider
    if(m_minPoint > val)
        val = m_minPoint;

    else if(m_maxPoint < val)
        val = m_maxPoint;

    m_sliderPosition.setY(val);

    //Redraw
    update();
}

void VerticalSimpleSlider::mousePressEvent(QMouseEvent *mouseEvent)
{
    m_beingClicked = true;
    updateSlider(mouseEvent->pos().y());
}

void VerticalSimpleSlider::mouseMoveEvent(QMouseEvent *event)
{
    if(m_beingClicked)
        updateSlider(event->pos().y());
}

float VerticalSimpleSlider::getCurrentValue() const
{
    //Get how far slider is in terms of percentage from left
    float distanceFromTop = (m_sliderPosition.y() - m_minPoint);
    float percentage = distanceFromTop / m_length;

    //Apply same percentage across min - max difference
    return m_min + (m_minMaxDiff * percentage);
}

void VerticalSimpleSlider::setValue(const float& val)
{
    //Calculate position from value
    const float lenghtPerUnit = m_length/m_minMaxDiff;
    const qreal distanceFromTop = val * lenghtPerUnit;
    float pos = m_minPoint + distanceFromTop;

    setSliderPosition(pos);
}


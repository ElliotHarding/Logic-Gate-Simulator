#ifndef SIMPLESLIDER_H
#define SIMPLESLIDER_H

#include <QWidget>
#include <QLayout>

class SimpleSlider : public QWidget
{
public:
    SimpleSlider(QWidget* pParent, const QRect& geometry, const float& min, const float& max, const uint& scrollSpeed, const QColor& sliderCol = QColor(255,255,255), const QColor& nubbleCol = Qt::lightGray);
    ~SimpleSlider() override;

    virtual float GetCurrentValue() const;
    virtual void SetValue(const float& val);

protected:

    //Events
    void mouseReleaseEvent(QMouseEvent *releaseEvent) override;
    void mousePressEvent(QMouseEvent* mouseEvent) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* paintEvent) override;
    virtual void wheelEvent(QWheelEvent *event) override;

    void UpdateSlider(const float& currentMousePos);
    virtual void SetSliderPosition(float val);

    virtual void UpdateParent(const float& val) = 0;

    //Colour stuff
    QColor m_sliderCol;
    QColor m_nubbleCol;

    //Position data
    QPoint m_sliderPosition;
    QPoint m_minPoint;
    QPoint m_maxPoint;

    //Scrolling
    uint m_scrollSpeed;

    bool m_beingClicked;

    //Pixel size (width)
    uint m_length;

    const float m_max;
    const float m_min;
    const float m_minMaxDiff;

    const int c_margin = 11;
};

class DLG_Home;
class ZoomSlider : public SimpleSlider
{
public:
    ZoomSlider(DLG_Home* parent, const QRect& layout, const float& min, const float& max, const uint& scrollSpeed);
    ~ZoomSlider();

private:
    virtual void UpdateParent(const float& val) override;
    DLG_Home* m_pParent;
};

class DLG_TextEdit;
class FontSlider : public SimpleSlider
{
public:
    FontSlider(DLG_TextEdit* parent, const QRect& layout, const float& min, const float& max, const uint& scrollSpeed);
    ~FontSlider();

private:
    virtual void UpdateParent(const float& val) override;
    DLG_TextEdit* m_pParent;    
};

class VerticalSimpleSlider : public SimpleSlider
{
public:
    VerticalSimpleSlider(QWidget* pParent, const QRect& layout, const float& min, const float& max, const uint& scrollSpeed);

    virtual float GetCurrentValue() const override;
    void SetValue(const float& val) override;

protected:
    virtual void UpdateParent(const float& val) override = 0;

private:
    void paintEvent(QPaintEvent* paintEvent) override;
    void mousePressEvent(QMouseEvent* mouseEvent) override;
    void mouseMoveEvent(QMouseEvent* event) override;

    void SetSliderPosition(float val) override;
};

class Widget_AllGates;
class GateSlider : public VerticalSimpleSlider
{
public:
    GateSlider(Widget_AllGates* parent, const QRect& layout, const float& min, const float& max, const uint& scrollSpeed);
    ~GateSlider();

private:
    void UpdateParent(const float& val) override;
    Widget_AllGates* m_pParent;    
};

#endif // SIMPLESLIDER_H

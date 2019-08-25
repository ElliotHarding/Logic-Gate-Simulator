#ifndef SIMPLESLIDER_H
#define SIMPLESLIDER_H

#include <QWidget>
#include <QLayout>

class SimpleSlider : public QWidget
{
public:
    SimpleSlider(QWidget* pParent, float min, float max, unsigned int scrollSpeed = 0, QColor sliderCol = QColor(255,255,255));
    ~SimpleSlider() override;

    virtual float GetCurrentValue();
    void SetValue(float val);

    void SetGeometry(QRect layout);

protected:

    //Events
    void mouseReleaseEvent(QMouseEvent *releaseEvent) override;
    void mousePressEvent(QMouseEvent* mouseEvent) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* paintEvent) override;
    virtual void wheelEvent(QWheelEvent *event) override;

    void UpdateSlider(float currentMousePos);
    virtual void SetSliderPosition(float val);

    virtual void UpdateParent(float val) = 0;

    //Colour stuff
    QColor m_sliderCol;

    //Position data
    QPoint m_sliderPosition;
    QPoint m_minPoint;
    QPoint m_maxPoint;

    //Scrolling
    unsigned int m_scrollSpeed;

    bool m_beingClicked;

    //Pixel size (width)
    int m_length;

    const float m_max;
    const float m_min;
    const float m_minMaxDiff;

    const int c_margin = 11;
};

class DLG_Home;
class ZoomSlider : public SimpleSlider
{
public:
    ZoomSlider(float min, float max, unsigned int scrollSpeed, DLG_Home* parent);
    ~ZoomSlider();

protected:

    DLG_Home* m_pParent;
    virtual void UpdateParent(float val);
};

class DLG_TextEdit;
class FontSlider : public SimpleSlider
{
public:
    FontSlider(float min, float max, unsigned int scrollSpeed, DLG_TextEdit* parent);
    ~FontSlider();

protected:
    DLG_TextEdit* m_pParent;
    virtual void UpdateParent(float val);
};

class VerticalSimpleSlider : public SimpleSlider
{
public:
    VerticalSimpleSlider(QWidget* pParent, float min, float max, unsigned int scrollSpeed = 0, QColor sliderCol = QColor(255,255,255));

    virtual float GetCurrentValue() override;
    void SetValue(float val);
    void SetGeometry(QRect layout);

    virtual void UpdateParent(float val) override = 0;

protected:
    void mousePressEvent(QMouseEvent* mouseEvent) override;
    void mouseMoveEvent(QMouseEvent* event) override;

    void SetSliderPosition(float val) override;
};

class Widget_AllGates;
class GateSlider : public VerticalSimpleSlider
{
public:
    GateSlider(float min, float max, Widget_AllGates* parent, QColor sliderCol = QColor(255,255,255));
    ~GateSlider();

protected:
    Widget_AllGates* m_pParent;
    virtual void UpdateParent(float val);
};

#endif // SIMPLESLIDER_H

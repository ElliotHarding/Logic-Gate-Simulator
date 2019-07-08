#ifndef SIMPLESLIDER_H
#define SIMPLESLIDER_H

#include <QWidget>

class SimpleSlider : public QWidget
{
public:
    SimpleSlider(float min, float max, QRect layout);
    ~SimpleSlider();

    float GetCurrentValue();
    void SetValue(float val);

protected:

    //Events
    void mouseReleaseEvent(QMouseEvent *releaseEvent) override;
    void mousePressEvent(QMouseEvent* mouseEvent) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* paintEvent) override;

    void UpdateSlider(float currentMousePosX);
    void SetSliderPosition(float val);

    virtual void UpdateParent(float val) = 0;

    //Position data
    QPoint m_sliderPosition;
    QPoint m_leftMost;
    QPoint m_rightMost;

    bool m_beingClicked;

    //Pixel size (width)
    const int m_width;

    const float m_max;
    const float m_min;
    const float m_minMaxDiff;

    const static int c_height = 30;
    const static int c_margin = 11;
};

class DLG_Home;
class ZoomSlider : public SimpleSlider
{
public:
    ZoomSlider(float min, float max, QRect layout, DLG_Home* parent);
    ~ZoomSlider();

protected:

    DLG_Home* m_pParent;
    virtual void UpdateParent(float val);
};

class DLG_TextEdit;
class FontSlider : public SimpleSlider
{
public:
    FontSlider(float min, float max, QRect layout, DLG_TextEdit* parent);
    ~FontSlider();

protected:
    DLG_TextEdit* m_pParent;
    virtual void UpdateParent(float val);
};

#endif // SIMPLESLIDER_H

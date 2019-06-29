#ifndef SIMPLESLIDER_H
#define SIMPLESLIDER_H

#include <QWidget>

class DLG_Home;

class SimpleSlider : public QWidget
{
public:
    SimpleSlider(float min, float max, QRect layout, DLG_Home* parent = nullptr);

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

    DLG_Home* m_pParent;

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

#endif // SIMPLESLIDER_H

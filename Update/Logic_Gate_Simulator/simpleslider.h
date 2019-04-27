#ifndef SIMPLESLIDER_H
#define SIMPLESLIDER_H

#include <QWidget>

class DLG_Home;

class SimpleSlider : public QWidget
{
public:
    SimpleSlider(float min, float max, QPoint pos, int size = 10, DLG_Home* parent = nullptr);

    float GetCurrentValue();

protected:

    //Events
    void mouseReleaseEvent(QMouseEvent *releaseEvent) override;
    void mousePressEvent(QMouseEvent* mouseEvent) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* paintEvent) override;

    void UpdateSlider(int currentMousePosX);

    DLG_Home* m_pParent;
    void sendData();

    //Position data
    QPoint m_sliderPosition;
    QPoint m_leftMost;
    QPoint m_rightMost;

    bool m_beingClicked;

    //Pixel size
    const int m_size;

    const float m_max;
    const float m_min;
    const float m_minMaxDiff;
};

#endif // SIMPLESLIDER_H

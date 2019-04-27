#ifndef SIMPLESLIDER_H
#define SIMPLESLIDER_H

#include <QWidget>

class SimpleSlider : public QWidget
{
public:
    SimpleSlider(float min, float max, QPoint pos, int size = 10, float incSize = 1, QWidget *parent = nullptr);

    float GetCurrentValue() {return m_currentValue;}

protected:

    //Events
    void mouseReleaseEvent(QMouseEvent *releaseEvent) override;
    void mousePressEvent(QMouseEvent* mouseEvent) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* paintEvent) override;

    QPoint m_position;

    int m_currentMousePosX;

    bool m_beingClicked;

    //Pixel size
    int m_size;

    float m_max;
    float m_min;
    float m_minMaxDiff;
    float m_currentValue;
    float m_incrementSize;
};

#endif // SIMPLESLIDER_H

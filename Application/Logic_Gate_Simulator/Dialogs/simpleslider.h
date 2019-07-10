#ifndef SIMPLESLIDER_H
#define SIMPLESLIDER_H

#include <QWidget>
#include <QLayout>

class SimpleSlider : public QWidget
{
public:
    SimpleSlider(QWidget* pParent, float min, float max);
    ~SimpleSlider() override;

    float GetCurrentValue();
    void SetValue(float val);

    void SetGeometry(QRect layout)
    {
        //Calculate positions & dimensions
        m_width = layout.width() - (c_margin * 2);

        m_leftMost = QPoint(c_margin, layout.height()/2);
        m_rightMost = QPoint(m_leftMost.x() + m_width, layout.height()/2);

        m_sliderPosition = m_leftMost;

        setGeometry(layout);
    }

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
    int m_width;

    const float m_max;
    const float m_min;
    const float m_minMaxDiff;

    const int c_margin = 11;
};

class DLG_Home;
class ZoomSlider : public SimpleSlider
{
public:
    ZoomSlider(float min, float max, DLG_Home* parent);
    ~ZoomSlider();

protected:

    DLG_Home* m_pParent;
    virtual void UpdateParent(float val);
};

class DLG_TextEdit;
class FontSlider : public SimpleSlider
{
public:
    FontSlider(float min, float max, DLG_TextEdit* parent);
    ~FontSlider();

protected:
    DLG_TextEdit* m_pParent;
    virtual void UpdateParent(float val);
};

#endif // SIMPLESLIDER_H

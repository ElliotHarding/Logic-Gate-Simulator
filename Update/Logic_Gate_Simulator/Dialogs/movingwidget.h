#ifndef MOVINGWIDGET_H
#define MOVINGWIDGET_H

#include <QWidget>

class MovingWidget : public QWidget
{
public:
    MovingWidget(QWidget *parent);

protected:
    void paintEvent(QPaintEvent* paintEvent) override;

    QBrush m_backgroundBrush;
};

#endif // MOVINGWIDGET_H

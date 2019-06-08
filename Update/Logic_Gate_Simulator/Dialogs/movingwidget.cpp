#include "movingwidget.h"
#include <QPainter>
#include <QBrush>

MovingWidget::MovingWidget(QWidget *parent) :
    QWidget (parent),
    m_backgroundBrush(QColor(255,255,255,255))
{    
}

void MovingWidget::MoveX(int xDir)
{
    //Move
    const QRect geo = geometry();
    move(geo.left() + xDir, geo.top());

    //request immediate re-draw
    repaint();
}

void MovingWidget::paintEvent(QPaintEvent* paintEvent)
{
    QPainter painter(this);

    QRect r = geometry();
    r.translate(-pos().x(), -pos().y());

    painter.fillRect(r, m_backgroundBrush);

    QWidget::paintEvent(paintEvent);
}

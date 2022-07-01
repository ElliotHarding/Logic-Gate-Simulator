#include "widget_spawnedgate.h"

#include "dlg_home.h"
#include "gate.h"

#include <QDebug>

Widget_SpawnedGate::Widget_SpawnedGate(DLG_Home* pHome) :
    QWidget(pHome),
    m_pHome(pHome),
    m_pSpawnedGate(nullptr)
{
    setGeometry(0, 0, m_pHome->geometry().width(), m_pHome->geometry().height());
    setMouseTracking(true);
}

void Widget_SpawnedGate::open(Gate* pSpawnedGate)
{
    m_pSpawnedGate = pSpawnedGate;
    QWidget::show();
}

void Widget_SpawnedGate::setZoomFactor(const qreal& zoomFactor)
{
    m_zoomFactor = zoomFactor;
}

void Widget_SpawnedGate::paintEvent(QPaintEvent*)
{
    if(m_pSpawnedGate)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::HighQualityAntialiasing, true);

        painter.translate(geometry().center().x(), geometry().center().y());
        painter.scale(m_zoomFactor, m_zoomFactor);

        m_pSpawnedGate->draw(painter);
    }
}

QPoint qtPointToWorldPoint(const QPoint& mousePoint, const qreal& zoomFactor, const QRect& geometry)
{
    QTransform transform;
    transform.scale(zoomFactor, zoomFactor);
    return transform.inverted().map(QPoint(mousePoint.x() - geometry.center().x(), mousePoint.y() - geometry.center().y()));
}

void Widget_SpawnedGate::mouseReleaseEvent(QMouseEvent* releaseEvent)
{
    if(m_pSpawnedGate)
    {
        QPoint pos = qtPointToWorldPoint(releaseEvent->pos(), m_zoomFactor, geometry());
        qDebug() << pos;
        //m_pSpawnedGate->setPosition(pos.x(), pos.y());
    }
}

void Widget_SpawnedGate::mouseMoveEvent(QMouseEvent* event)
{
    if(m_pSpawnedGate)
    {
        QPoint pos = qtPointToWorldPoint(event->pos(), m_zoomFactor, geometry());
        //m_pSpawnedGate->setPosition(pos.x(), pos.y());
    }
}

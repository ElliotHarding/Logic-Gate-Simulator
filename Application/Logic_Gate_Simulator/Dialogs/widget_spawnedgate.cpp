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

        painter.scale(m_zoomFactor, m_zoomFactor);

        m_pSpawnedGate->draw(painter);
    }
}

void Widget_SpawnedGate::mouseReleaseEvent(QMouseEvent* releaseEvent)
{
    qDebug() << releaseEvent->pos();
}

void Widget_SpawnedGate::mouseMoveEvent(QMouseEvent* event)
{
    qDebug() << event->pos();
}

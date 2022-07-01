#include "widget_spawnedgate.h"

#include "dlg_home.h"
#include "gate.h"

#include <QDebug>

Widget_SpawnedGate::Widget_SpawnedGate(DLG_Home* pHome) :
    QWidget(pHome),
    m_pHome(pHome),
    m_pSpawnedGate(nullptr)
{
    setGeometry(0, 0, 200, 200);
}

void Widget_SpawnedGate::open(Gate* pSpawnedGate, const uint& x, const uint& y)
{
    setGeometry(x, y, 200, 200);
    m_pSpawnedGate = pSpawnedGate;
    m_pSpawnedGate->setPosition(geometry().center().x(), geometry().center().y());
    QWidget::show();
}

void Widget_SpawnedGate::paintEvent(QPaintEvent*)
{
    if(m_pSpawnedGate)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::HighQualityAntialiasing, true);

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

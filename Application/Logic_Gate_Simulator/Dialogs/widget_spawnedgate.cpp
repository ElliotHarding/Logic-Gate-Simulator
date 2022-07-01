#include "widget_spawnedgate.h"

#include "dlg_home.h"
#include "gate.h"

#include <QDebug>

namespace Settings
{
const QColor GateDraggingBackgroundColor = QColor(20, 20, 20, 1);
}

Widget_SpawnedGate::Widget_SpawnedGate(DLG_Home* pHome) :
    QDialog(pHome),
    m_pHome(pHome),
    m_pSpawnedGate(nullptr)
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_PaintOnScreen);

    setGeometry(m_pHome->geometry());
    setMouseTracking(true);
}

QPoint qtPointToPaintPoint(const QPoint& mousePoint, const qreal& zoomFactor)
{
    QTransform transform;
    transform.scale(zoomFactor, zoomFactor);
    return transform.inverted().map(mousePoint);
}

//////////////////
/// \brief Widget_SpawnedGate::open
/// \param pSpawnedGate gate to try drop onto GateField
/// \param spawnPosition DLG_Home (and Widget_SpawnedGate) relative spawn position
///
void Widget_SpawnedGate::open(Gate* pSpawnedGate, const QPoint& spawnPosition)
{
    const QPoint paintPosition = qtPointToPaintPoint(spawnPosition, m_zoomFactor);
    m_pSpawnedGate = pSpawnedGate;
    m_pSpawnedGate->setPosition(paintPosition.x(), paintPosition.y());
    setFocus(Qt::MouseFocusReason);
    setGeometry(m_pHome->geometry());
    QDialog::show();
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

        painter.fillRect(QRect(0, 0, geometry().width(), geometry().height()), Settings::GateDraggingBackgroundColor);

        painter.scale(m_zoomFactor, m_zoomFactor);

        m_pSpawnedGate->draw(painter);
    }
}

void Widget_SpawnedGate::mouseReleaseEvent(QMouseEvent* releaseEvent)
{
    if(m_pSpawnedGate)
    {
        //Set position relative to Widget_SpawnedGate (same as DLG_Home)
        m_pSpawnedGate->setPosition(releaseEvent->pos().x(), releaseEvent->pos().y());

        m_pHome->AddGateToGateField(m_pSpawnedGate);

        m_pSpawnedGate = nullptr;
        QDialog::hide();
    }
}

void Widget_SpawnedGate::mousePressEvent(QMouseEvent* mouseEvent)
{
    if(m_pSpawnedGate)
    {
        //Set position relative to Widget_SpawnedGate (same as DLG_Home)
        m_pSpawnedGate->setPosition(mouseEvent->pos().x(), mouseEvent->pos().y());

        m_pHome->AddGateToGateField(m_pSpawnedGate);

        m_pSpawnedGate = nullptr;
        QDialog::hide();
    }
}

void Widget_SpawnedGate::mouseMoveEvent(QMouseEvent* event)
{
    if(m_pSpawnedGate)
    {
        const QPoint pos = qtPointToPaintPoint(event->pos(), m_zoomFactor);
        m_pSpawnedGate->setPosition(pos.x(), pos.y());
        update();
    }
}

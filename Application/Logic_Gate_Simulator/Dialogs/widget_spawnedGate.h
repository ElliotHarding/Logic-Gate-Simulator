#ifndef WIDGET_SPAWNEDGATE_H
#define WIDGET_SPAWNEDGATE_H

#include <QDialog>
#include "gate.h"

class DLG_Home;

//This is actaully a dialog not a widget... could rename...
class Widget_SpawnedGate : public QDialog
{
    Q_OBJECT
public:
    Widget_SpawnedGate(DLG_Home* pHome);

    void open(Gate* pSpawnedGate, const QPoint& spawnPosition);
    void setZoomFactor(const qreal& zoomFactor);

protected:
    void paintEvent(QPaintEvent* paintEvent) override;

    void mouseReleaseEvent(QMouseEvent *releaseEvent) override;
    void mousePressEvent(QMouseEvent* mouseEvent) override;
    void mouseMoveEvent(QMouseEvent* event) override;

    DLG_Home* m_pHome;
    Gate* m_pSpawnedGate;
    qreal m_zoomFactor;
};

#endif // WIDGET_SPAWNEDGATE_H

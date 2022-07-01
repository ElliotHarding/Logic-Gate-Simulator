#ifndef WIDGET_SPAWNEDGATE_H
#define WIDGET_SPAWNEDGATE_H

#include <QWidget>

class DLG_Home;
class Gate;

class Widget_SpawnedGate : public QWidget
{
    Q_OBJECT
public:
    Widget_SpawnedGate(DLG_Home* pHome);

    void open(Gate* pSpawnedGate, const uint& x, const uint& y);

protected:
    void paintEvent(QPaintEvent* paintEvent) override;

    void mouseReleaseEvent(QMouseEvent *releaseEvent) override;
    void mouseMoveEvent(QMouseEvent* event) override;

    DLG_Home* m_pHome;
    Gate* m_pSpawnedGate;
};

#endif // WIDGET_SPAWNEDGATE_H

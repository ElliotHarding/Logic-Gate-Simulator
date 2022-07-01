#ifndef WIDGET_SPAWNEDGATE_H
#define WIDGET_SPAWNEDGATE_H

#include <QWidget>

class DLG_Home;
class Gate;

class Widget_SpawnedGate : public QWidget
{
    Q_OBJECT
public:
    Widget_SpawnedGate(DLG_Home* pHome, Gate* pSpawnedGate);

protected:
    void paintEvent(QPaintEvent* paintEvent) override;

    DLG_Home* m_pHome;
    Gate* m_pSpawnedGate;
};

#endif // WIDGET_SPAWNEDGATE_H

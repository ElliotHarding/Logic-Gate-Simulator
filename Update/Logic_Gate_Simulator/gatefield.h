#ifndef GATEFIELD_H
#define GATEFIELD_H

#include <QWidget>
#include "clickmode.h"
#include "gate.h"
#include "gateinputbox.h"
#include "QMouseEvent"
#include <QDragMoveEvent>

class GateField : public QWidget
{
    Q_OBJECT
public:

    explicit GateField(QWidget *parent = nullptr);
    ~GateField() override;

    //Calls from DLG_Home:
    void addGameObject(Gate* go);
    void updateFunction();
    void setCurrentClickMode(ClickMode clickMode) {m_currentClickMode = clickMode;}

signals:
public slots:
protected:
private:

    //Events
    void mouseReleaseEvent(QMouseEvent *releaseEvent) override;
    void mousePressEvent(QMouseEvent* mouseEvent) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* paintEvent) override;

    void setUpdateGraphics();

    //Gates
    std::vector<Gate*> m_allGates;
    QMutex m_lockAllGates;

    //Temps for multi step linking and unlinking
    Node* m_linkNodeA = nullptr;

    //Clicking
    ClickMode m_currentClickMode = CLICK_DRAG;
    bool m_bMouseDragging = false;
    bool m_bMouseDown = false;
    void linkNodesClick(int clickX, int clickY);
    void deleteClick(int clickX, int clickY);
    void dragClick(int clickX, int clickY);
    void deleteLinkedNodesClick(int clickX, int clickY);
    void anyInputGatesToggled(int clickX, int clickY);

    //Coords of newly spawned gate
    const int SPAWN_X = 300;
    const int SPAWN_Y = 300;
};

#endif // GATEFIELD_H

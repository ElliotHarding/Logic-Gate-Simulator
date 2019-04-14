#ifndef GATEFIELD_H
#define GATEFIELD_H

#include <QWidget>
#include "clickmode.h"
#include "gate.h"
#include "QMouseEvent"
#include <QDragMoveEvent>

class GateField : public QWidget
{
    Q_OBJECT
public:
    explicit GateField(QWidget *parent = nullptr);
    ~GateField() override;

    void addGameObject(Gate* go);

    //Comes from DLG_Home...
    void setCurrentClickMode(ClickMode clickMode) {m_currentClickMode = clickMode;}

signals:

public slots:

protected:

private:
    void mouseReleaseEvent(QMouseEvent *releaseEvent) override;
    void mousePressEvent(QMouseEvent* mouseEvent) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* paintEvent) override;

    void updateFunction();

    //Gates
    std::vector<Gate*> m_allGates;

    Node* m_linkNodeA = nullptr;

    //Clicking
    ClickMode m_currentClickMode = CLICK_DRAG;
    bool m_bMouseDragging = false;
    void linkNodesClick(int clickX, int clickY);
    void deleteClick(int clickX, int clickY);
    void defaultClick(int clickX, int clickY);
    void dragClick(int clickX, int clickY);

    //Coords of newly spawned gate
    const int SPAWN_X = 5;
    const int SPAWN_Y = 5;
};

#endif // GATEFIELD_H

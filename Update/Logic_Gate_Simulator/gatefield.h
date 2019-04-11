#ifndef GATEFIELD_H
#define GATEFIELD_H

#include <QWidget>
#include "clickmode.h"
#include "gate.h"
#include "QMouseEvent"

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

    void mousePressEvent(QMouseEvent* mouseEvent) override;
    void paintEvent(QPaintEvent* paintEvent) override;

    std::vector<Gate*> m_allGates;
    void runGates();

    Node* m_linkNodeA = nullptr;

    //Clicking
    ClickMode m_currentClickMode = CLICK_DRAG;
    void linkNodesClick(int clickX, int clickY);
    void dragClick(int clickX, int clickY);
    void deleteClick(int clickX, int clickY);
    void defaultClick(int clickX, int clickY);

    //Coords of newly spawned gate
    const int SPAWN_X = 1;
    const int SPAWN_Y = 1;
};

#endif // GATEFIELD_H

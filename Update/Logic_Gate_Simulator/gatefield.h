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
    void paintEvent(QPaintEvent* paintEvent) override;

    void addGameObject(Gate* go);

    void handleInput(int clickX, int clickY, ClickMode clickMode);

    void runGates();

signals:

public slots:

protected:
    void mousePressEvent(QMouseEvent* mouseEvent) override;

private:
    std::vector<Gate*> m_allGates;

    void linkNodesClick(int clickX, int clickY);
    void dragClick(int clickX, int clickY);
    void deleteClick(int clickX, int clickY);
    void defaultClick(int clickX, int clickY);

    Node* m_linkNodeA = nullptr;

    ClickMode m_currentClickMode = CLICK_DRAG;

    //Coords of newly spawned gate
    const int SPAWN_X = 50;
    const int SPAWN_Y = 50;
};

#endif // GATEFIELD_H

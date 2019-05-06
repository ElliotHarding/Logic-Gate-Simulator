#ifndef GATEFIELD_H
#define GATEFIELD_H

#include <QWidget>
#include <QMouseEvent>
#include <QDragMoveEvent>
#include <QRubberBand>
#include <QMainWindow>

#include "clickmode.h"
#include "gate.h"
#include "GateToggle.h"
#include "GateTimer.h"
#include "gatecollection.h"

class DLG_SaveGateCollection;
class DLG_Home;

class GateField : public QWidget
{
    Q_OBJECT
public:

    explicit GateField(qreal zoomFactor, std::string name, DLG_Home* parent);
    ~GateField() override;

    void addGameObject(Gate* go, bool newlySpawned = true);
    void updateFunction();
    void setCurrentClickMode(ClickMode clickMode) {m_currentClickMode = clickMode;}
    void setZoomLevel(qreal zoom) {m_zoomFactor = zoom;}
    GateCollection* GenerateGateCollection();
    bool SaveData();
    void DeleteGate(Gate* g);

    bool Enabled = true;

signals:
public slots:
protected:
private:

    //Events
    void mouseReleaseEvent(QMouseEvent *releaseEvent) override;
    void mousePressEvent(QMouseEvent* mouseEvent) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* paintEvent) override;

    void moveToFront(int index, std::vector<Gate*>& vec);

    //Communication with parent dialog (DLG_Home instance)
    DLG_Home* m_pParent;
    void updateGateSelected(Gate* g);

    //Saving
    std::string m_name = "Unknown";

    //Gates
    std::vector<Gate*> m_allGates;
    QMutex m_lockAllGates;

    //Temps for multi step linking and unlinking
    Node* m_linkNodeA = nullptr;

    //Zooming
    qreal m_zoomFactor;

    //Clicking
    ClickMode m_currentClickMode = CLICK_DRAG;
    bool m_bMouseDragging = false;

    //Selecting
    QRubberBand* m_selectionTool = nullptr;
    QPoint m_selectionToolOrigin;
    const QColor selectionAreaColor = Qt::blue;
    std::vector<Gate*> m_selectedGates;
    DLG_SaveGateCollection* m_saveGateCollection;

    //Mouse event handlers
    void linkNodesClick(int clickX, int clickY);
    void deleteClick(int clickX, int clickY);
    void dragClick(int clickX, int clickY);
    void deleteLinkedNodesClick(int clickX, int clickY);
    //void anyInputGatesToggled(int clickX, int clickY);
    void defaultClick(int clickX, int clickY);
    void selectionClick(int clickX, int clickY);

    //Coords of newly spawned gate
    const int SPAWN_X = 300;
    const int SPAWN_Y = 300;
};

#endif // GATEFIELD_H

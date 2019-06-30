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

    //Construction
    explicit GateField(qreal zoomFactor, std::string name, DLG_Home* parent, DLG_SaveGateCollection* saveGateCollectionDialog);
     ~GateField() override;

    void addGameObject(Gate* go, bool newlySpawned = true);
    void setCurrentClickMode(ClickMode clickMode);
    bool SaveGateCollection(std::ofstream& saveStream);
    void setZoomLevel(qreal zoom);
    void DeleteGate(Gate* g);
    void updateFunction();
    bool SaveData();
    void Undo();
    void Redo();

    bool Enabled = true;

signals:
public slots:
protected:
private:

    //Mouse event handlers
    void linkNodesClick(int clickX, int clickY);
    void deleteClick(int clickX, int clickY);
    void dragClick(int clickX, int clickY);
    void deleteLinkedNodesClick(int clickX, int clickY);
    void defaultClick(int clickX, int clickY);
    void selectionClick(int clickX, int clickY);
    void panClick(int clickX, int clickY);

    //Events
    void mouseReleaseEvent(QMouseEvent *releaseEvent) override;
    void mousePressEvent(QMouseEvent* mouseEvent) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* paintEvent) override;

    void leftMouseClick(int clickX, int clickY);
    void rightMouseClick(int clickX, int clickY);
    void middleMouseClick(int clickX, int clickY);

    //Communication with parent dialog (DLG_Home instance)
    DLG_Home* m_pParent;
    void updateGateSelected(Gate* g);

    //Saving
    std::string m_name = "Unknown";

    //Gates
    QMutex m_lockAllGates;
    std::vector<Gate*> m_allGates;
    Gate* m_dragGate = nullptr;
    void moveToFront(int index, std::vector<Gate*>& vec);

    //Gate backups for redo and undo functions
    void BackupGates();
    std::vector<std::vector<Gate*>> m_gateBackups;
    const int c_maxNumberOfBackups = 10;
    int m_backupIndex = 0;

    //Temps for multi step linking and unlinking
    Node* m_linkNodeA = nullptr;

    //Zooming
    qreal m_zoomFactor;
    QPoint GetClickFromMouseEvent(QMouseEvent* mouseEvent) const;

    //Panning
    Vector2D m_screenPosDelta;
    QPoint m_previousDragMousePos;
    const float c_panSpeedMultiplier = 0.75;

    //Clicking
    ClickMode m_currentClickMode = CLICK_DRAG;
    bool m_bMouseDragging = false;

    //Selecting
    QRubberBand* m_selectionTool = nullptr;
    QPoint m_selectionToolOrigin;
    const QColor selectionAreaColor = Qt::blue;
    std::vector<Gate*> m_selectedGates;
    DLG_SaveGateCollection* m_pDlgSaveGateCollection;

    //Coords of newly spawned gate
    const int SPAWN_X = 300;
    const int SPAWN_Y = 300;
};

#endif // GATEFIELD_H

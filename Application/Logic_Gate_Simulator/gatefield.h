#ifndef GATEFIELD_H
#define GATEFIELD_H

#include <QWidget>
#include <QMouseEvent>
#include <QDragMoveEvent>
#include <QRubberBand>
#include <QMainWindow>
#include <QMutex>
#include <QThread>

#include "clickmode.h"
#include "gate.h"
#include "GateToggle.h"
#include "GateTimer.h"
#include "gatecollection.h"

class DLG_SaveGateCollection;
class DLG_Home;
class TextLabel;

class GateField : public QWidget
{
    Q_OBJECT
public:

    //Construction
    explicit GateField(qreal zoomFactor, std::string name, DLG_Home* parent, DLG_SaveGateCollection* saveGateCollectionDialog, bool disableGateCollections = false, bool disableGateBackup = false, bool disableZoom = false);
     ~GateField() override;

    //Gates
    void AddGate(Gate* go, bool newlySpawned = true, bool cameFromGateColleciton = false);
    void DeleteGate(Gate* g);
    void ForgetChild(Gate* g);

    //Saving
    bool SaveGateCollection(std::ofstream& saveStream);
    void StartSaveGateCollection(std::vector<Gate*> selectedGates);
    bool SaveData();
    void SaveData(std::ofstream& saveFile);

    //Actions
    void Undo();
    void Redo();
    void SetZoomLevel(qreal zoom, bool zoomCenter = true);

    //Called if don't want the next gate to be clicked to be set as the selected gate
    void SkipNextGateSelectedCall(bool stopDragging = false);
    void StopDragging();

    //DLG_Home stuff
    void EditTextLabel(TextLabel *textLabelToEdit);
    void UpdateGateSelected(Gate* g);

    //Timer thread mutex bypass for m_allGates
    std::vector<Gate*>& GetGates();
    void FinishWithGates();    

    //Public vars
    bool Enabled = true;
    ClickMode CurrentClickMode;
    ClickMode GetCurrentClickMode();

signals:
public slots:
protected:
private:

    //Functions with rl_ require m_lockAllGates to be locked

    //Mouse event delegates
    QPoint QtPointToWorldPoint(QPoint mousePoint) const;
    void rl_leftMouseClick(int clickX, int clickY);

    //Click actions
    bool rl_linkNodesClick(int clickX, int clickY);
    void rl_deleteClick(int clickX, int clickY);
    bool rl_dragClick(int clickX, int clickY);
    void rl_deleteLinkedNodesClick(int clickX, int clickY);
    bool rl_defaultClick(int clickX, int clickY);
    void rl_selectionClick(int clickX, int clickY);
    void rl_panClick(int clickX, int clickY);

    //Qt Events
    void mouseReleaseEvent(QMouseEvent *releaseEvent) override;
    void mousePressEvent(QMouseEvent* mouseEvent) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* paintEvent) override;
    void wheelEvent(QWheelEvent *event) override;

    void rl_updateFunction();

    DLG_Home* m_pParent;

    //DLG_Task settings
    bool m_bDisableGateCollections;

    //Causes next UpdateGateSelected call to not do anything
    bool m_bSkipUpdateGateSelected = false;

    //Saving
    std::string m_name = "Unknown";

    //Gates
    QMutex m_lockAllGates;
    std::vector<Gate*> m_allGates;
    Gate* m_dragGate = nullptr;    
    void moveToFront(int index, std::vector<Gate*>& vec);

    //Gate backups for redo and undo functions
    void rl_backupGates();
    std::vector<std::vector<Gate*>> m_gateBackups;
    bool m_bDisableGateBackup;
    const int c_maxNumberOfBackups = 10;
    int m_backupIndex = 0;

    //Temps for multi step linking and unlinking
    Node* m_linkNodeA = nullptr;

    //Zooming
    qreal m_zoomFactor;
    bool m_bDisableZoom = false;
    QPoint m_centerScreen;
    const qreal m_zoomScrollSpeed = 0.05;

    //Panning
    Vector2D m_screenPosDelta;
    QPoint m_previousDragMousePos;
    const float c_panSpeedMultiplier = 0.75;
    void rl_offsetGates(double offsetX, double offsetY);

    //Dragging
    QPoint m_currentDragPoint = QPoint(0,0);
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

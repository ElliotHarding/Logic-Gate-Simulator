#ifndef GATEFIELD_H
#define GATEFIELD_H

#include <QWidget>
#include <QMouseEvent>
#include <QDragMoveEvent>
#include <QRubberBand>
#include <QMainWindow>
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
    GateField(qreal zoomFactor, std::string name, DLG_Home* parent, DLG_SaveGateCollection* saveGateCollectionDialog, bool disableGateCollections = false, bool disableGateBackup = false, bool disableZoom = false);
    ~GateField();

    //Gates
    std::vector<Gate*>& GetGates();
    void AddGate(Gate* go, bool newlySpawned = true);
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
    void SetZoomLevel(qreal zoom);

    //DLG_Home stuff
    void EditTextLabel(TextLabel *textLabelToEdit);
    void UpdateGateSelected(Gate* g);   

    //Public vars
    bool Enabled = true;
    ClickMode CurrentClickMode;
    ClickMode GetCurrentClickMode();

signals:
public slots:
protected:
private:
    //Mouse event delegates
    QPoint QtPointToWorldPoint(QPoint mousePoint) const;
    void rl_leftMouseClick(int clickX, int clickY);

    //Click actions
    void checkStartLink(const int& clickX, const int& clickY);
    void rl_deleteClick(int clickX, int clickY);
    void checkStartDrag(const int& clickX, const int& clickY);
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

    //Saving
    std::string m_name = "Unknown";

    //Gates
    std::vector<Gate*> m_allGates;   
    void moveToFront(int index, std::vector<Gate*>& vec);

    //Gate backups for redo and undo functions
    void rl_backupGates();
    std::vector<std::vector<Gate*>> m_gateBackups;
    bool m_bDisableGateBackup;
    const int c_maxNumberOfBackups = 10;
    int m_backupIndex = 0;

    //Temps for multi step linking and unlinking
    Node* m_linkNodeA = nullptr;
    QPoint m_currentMousePos;

    //Zooming
    qreal m_zoomFactor;
    bool m_bDisableZoom = false;
    const qreal m_zoomScrollSpeed = 0.05;

    //Panning
    struct Vector2D {int x; int y;};
    Vector2D m_screenPosDelta;
    QPoint m_previousDragMousePos;
    const float c_panSpeedMultiplier = 0.75;
    void rl_offsetGates(double offsetX, double offsetY);

    //Dragging
    bool m_bMouseDown = false;
    Gate* m_pDraggingGate = nullptr;

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

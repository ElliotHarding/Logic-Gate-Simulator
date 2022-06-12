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

////////////////////////////////////////////////////////////////////////////////////////
/// GateFieldHistory
///
/// Records history of GateField
///
/// TODO : Only record changes, not entire list of gates
class GateFieldHistory
{
public:
    void recordHistory(const std::vector<Gate*>& snapshot);
    bool undoHistory(std::vector<Gate*>& currentSnapshot);
    bool redoHistory(std::vector<Gate*>& currentSnapshot);

    ~GateFieldHistory();
private:
    std::vector<std::vector<Gate*>> m_history;
    uint m_historyIndex = 0;
};

////////////////////////////////////////////////////////////////////////////////////////
/// GateField
///
class GateField : public QWidget
{
    Q_OBJECT
public:

    //Construction
    GateField(DLG_Home* pParent, const qreal& zoomFactor, const std::string& name, DLG_SaveGateCollection* pSaveGateCollectionDialog);
    ~GateField();

    //Gates
    void AddGate(Gate* go, const bool& newlySpawned = true);
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
    void SetZoomLevel(const qreal& zoom);

    //DLG_Home stuff
    void EditTextLabel(TextLabel *textLabelToEdit);
    void UpdateGateSelected(Gate* g);   

    ///Click mode
    ClickMode GetCurrentClickMode();
    void setCurrentClickMode(const ClickMode& mode);

signals:
public slots:
protected:
private:
    //Mouse event delegates
    QPoint qtPointToWorldPoint(const QPoint& mousePoint) const;

    //Click actions
    bool checkStartLink(const QPoint& mouse);
    void checkEndLink(const QPoint& mouse);
    void checkDelete(const QPoint& mouse);
    void checkStartDrag(const QPoint& mouse);
    bool checkGateSelect(const QPoint& mouse);
    void checkDeleteNodeLink(const QPoint& mouse);
    void editSelection(const QPoint& mouse);
    void doPan(const QPoint& mouse);

    //Qt Events
    void mouseReleaseEvent(QMouseEvent *releaseEvent) override;
    void mousePressEvent(QMouseEvent* mouseEvent) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* paintEvent) override;
    void wheelEvent(QWheelEvent *event) override;

    DLG_Home* m_pParent;

    //Saving
    std::string m_name = "Unknown";

    //Gates
    std::vector<Gate*> m_allGates;   
    void moveToFront(const uint& index, std::vector<Gate*>& vec);

    //Gate history for redo and undo functions
    GateFieldHistory m_history;

    //Temps for multi step linking and unlinking
    Node* m_pLinkingNode = nullptr;
    QPoint m_currentMousePos;//Only correct during linking

    //Zooming
    qreal m_zoomFactor;

    //Panning
    QPoint m_previousDragMousePos;
    void offsetGates(const double& offsetX, const double& offsetY);

    //Dragging
    bool m_bMouseDown = false;
    Gate* m_pDraggingGate = nullptr;

    //Selecting
    QRubberBand* m_pSelectionTool = nullptr;
    QPoint m_selectionToolOrigin;
    std::vector<Gate*> m_selectedGates;
    DLG_SaveGateCollection* m_pDlgSaveGateCollection;

    ClickMode m_currentClickMode;
};

#endif // GATEFIELD_H

#ifndef GATEFIELD_H
#define GATEFIELD_H

#include <QWidget>
#include <QMouseEvent>
#include <QDragMoveEvent>
#include <QRubberBand>
#include <QMainWindow>
#include <QTimer>
#include <QDomDocument>

#include "clickmode.h"

namespace Settings
{
const QString GateFieldElement = "GateField";
const QString GateFieldFrequencyTag = "Frequency";
}

class DLG_Home;
class TextLabel;
class GateFPGA;
class Gate;
class GateCollection;
class Node;
struct TruthTable;
struct BooleanExpression;

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
    GateField(DLG_Home* pParent, const qreal& zoomFactor, const QString& name, const uint& updateFrequency = 200);
    ~GateField();

    //Gates
    void AddGate(Gate* go, const bool& newlySpawned = true);
    void ForgetChild(Gate* g);
    void ForgetUpdateRequest(Gate* g);
    void RequestUpdateGate(Gate* g);

    //Saving
    void StartSaveGateCollection(GateCollection* pGateCollection);
    void setName(const QString& name);
    QString name() const;
    void SaveData(QDomDocument& saveFile);

    //Actions
    void Undo();
    void Redo();
    void SetZoomLevel(const qreal& zoom);

    //DLG_Home stuff
    void UpdateGateSelected(Gate* g);
    void SendUserMessage(const QString& message);

    ///Update frequency
    void setUpdateFrequency(const uint& frequencyMs);
    uint updateFrequency() const;

signals:
public slots:
private slots:
    void onRequestUpdateGates();
protected:
private:
    //Mouse event delegates
    QPoint qtPointToWorldPoint(const QPoint& mousePoint) const;

    //Click actions
    bool checkStartLink(const QPoint& mouse);
    void checkEndLink(const QPoint& mouse);
    void checkDelete(const QPoint& mouse);
    bool checkStartDrag(const QPoint& mouse);
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
    QString m_name = "Unknown";

    //Gates
    std::vector<Gate*> m_allGates;
    std::vector<Gate*> m_gatesToUpdate;
    void moveToFront(const uint& index, std::vector<Gate*>& vec);
    uint m_gateUpdateFrequencyMs = 200;

    //Gate update
    QTimer m_gateUpdateTimer;

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
};

#endif // GATEFIELD_H

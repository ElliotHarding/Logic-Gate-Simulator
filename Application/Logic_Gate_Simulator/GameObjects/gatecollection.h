#ifndef GATECOLLECTION_H
#define GATECOLLECTION_H

#include "gate.h"

class GateCollection : public Gate
{
public:
    GateCollection(std::vector<Gate*> gates);
    ~GateCollection();

    virtual void UpdateOutput() override;
    virtual void draw(QPainter& painter) override;

    ///Position
    virtual void offsetPosition(const int& dX, const int& dY) override;
    virtual void setPosition(const int& x, const int& y) override;

    virtual GameObject* checkClicked(const QPoint& mouse) override;

    virtual bool FindNodeWithId(const id& id, Node*& pNode) override;
    virtual void AssignNewNodeIds() override;
    virtual void collectLinkInfo(std::vector<NodeIds>& collection) override;

    virtual void SetParent(GateField* gf) override;

    virtual void SaveData(std::ofstream& storage) override;

    virtual Gate* Clone() override;

    ///Drag mode
    void ToggleDragMode();
    bool IsDragAll();

    ///Gate adding and removing
    void AddGate(Gate* g);
    void ForgetGate(Gate* g);

protected:
    void ProporgateParentAndCheckForNestedGates();

    //Vector of all the gates within collection
    std::vector<Gate*> m_gates;

private:
    void UpdateContaningArea();

    ///Dragging
    enum DragMode{DragIndividual,DragAll};
    DragMode m_dragMode = DragAll;

    //QRect m_optimize;
    //QRect m_nandOptimize;
    QRect m_saveButton;
    QRect m_deleteButton;
    QRect m_deleteAllButton;
    QRect m_dragAllButton;
    void DrawButtons(QPainter& painter);
    bool CheckButtonClick(int clickX, int clickY);

    bool m_bDontDeleteGates = false;
};

#endif // GATECOLLECTION_H

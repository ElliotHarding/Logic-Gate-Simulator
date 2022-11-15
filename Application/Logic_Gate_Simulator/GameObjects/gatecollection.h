#ifndef GATECOLLECTION_H
#define GATECOLLECTION_H

#include "gate.h"
#include "truthtable.h"

class GateCollection : public Gate
{
public:
    GateCollection(std::vector<Gate*> gates);
    ~GateCollection();

    void setDeleteAll();

    virtual void updateOutput() override;
    virtual void draw(QPainter& painter) override;

    ///Position
    virtual void offsetPosition(const int& dX, const int& dY) override;
    virtual void setPosition(const int& x, const int& y) override;

    virtual GameObject* checkClicked(const QPoint& mouse) override;

    ///Node information
    virtual Node* checkClickedNodes(const QPoint& mouse) override;
    virtual bool findNodeWithId(const id& id, Node*& pNode) override;
    virtual void assignNewNodeIds() override;
    virtual void collectLinkInfo(std::vector<NodeIds>& collection) override;

    virtual void setParent(GateField* gf) override;

    virtual void saveData(QDomDocument& storage, QDomElement& parentElement) override;

    virtual Gate* clone() override;

    TextLabel* findTextLabelWithId(int id);
    void switchAttachedLabels(std::vector<Gate*> gates) override;

    ///Drag mode
    void toggleDragMode();

    ///Gate adding and removing
    void addGate(Gate* g);
    void forgetGate(Gate* g);

    void updateContaningArea();

    bool generateTruthTable(TruthTable& table);

protected:
    //Vector of all the gates within collection
    std::vector<Gate*> m_gates;

private:
    ///Dragging
    enum DragMode{DragIndividual,DragAll};
    DragMode m_dragMode = DragAll;
};

#endif // GATECOLLECTION_H

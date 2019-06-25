#ifndef GATECOLLECTION_H
#define GATECOLLECTION_H

#include "gate.h"

struct Vector2D {int x; int y;};

class GateCollection : public Gate
{
public:
    GateCollection(std::vector<Gate*> gates);
    ~GateCollection() override;

    virtual void UpdateOutput() override;
    virtual void UpdateGraphics(QPainter* painter) override;
    virtual bool UpdateDrag(int clickX, int clickY) override;
    virtual Node *GetClickedNode(int clickX, int clickY) override;
    virtual bool FindNodeWithId(id _id, Node*& n) override;
    virtual void OffsetPosition(int dX, int dY) override;
    virtual void AssignNewNodeIds() override;
    virtual bool DeleteClick(int clickX, int clickY) override;
    virtual bool UpdateClicked(int clickX, int clickY) override;

    virtual void SaveData(std::ofstream& storage) override;
    static void SaveData(std::ofstream& storage, std::vector<Gate*> gates);

    virtual Gate* Clone() override;

    Gate *UpdateClicked_Override(int clickX, int clickY);

    //Class specific public methods
    void DisplaceGates(Vector2D displacement);
    void UpdateContaningArea() {m_contaningArea = containingArea();}

    //Call UpdateContaningArea() before calling any of these
    virtual int Left() override {return m_contaningArea.left() + c_borderBoxMargin;}
    virtual int Right() override{return m_contaningArea.right() - c_borderBoxMargin;}
    virtual int Top() override {return m_contaningArea.top() + c_borderBoxMargin;}
    virtual int Bottom() override {return m_contaningArea.bottom() - c_borderBoxMargin;}

    //Drag mode
    void ToggleDragMode();
    bool IsDragAll();

private:
    //Vector of all the gates within collection
    std::vector<Gate*> m_gates;

    //Number of pixels from border before gates are seen
    const int c_borderBoxMargin = 20;

    QRect containingArea();
    QRect m_contaningArea;

    enum DragMode{DragIndividual,DragAll};
    DragMode m_dragMode = DragAll;
};

#endif // GATECOLLECTION_H

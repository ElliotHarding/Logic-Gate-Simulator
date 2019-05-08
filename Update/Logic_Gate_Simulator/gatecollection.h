#ifndef GATECOLLECTION_H
#define GATECOLLECTION_H

#include "gate.h"

struct Vector2D {int x; int y;};

enum DragMode{DragIndividual,DragAll};

class GateCollection : public Gate
{
public:
    GateCollection(std::vector<Gate*> gates);
    GateCollection(const GateCollection& gCopy);
    ~GateCollection() override;

    virtual void UpdateOutput() override;
    virtual void UpdateGraphics(QPainter* painter) override;
    virtual bool UpdateDrag(int clickX, int clickY) override;
    virtual bool UpdateClicked(int clickX, int clickY) override;
    virtual Node *GetClickedNode(int clickX, int clickY) override;
    virtual void SaveData(std::ofstream& storage) override;

    void DisplaceGates(Vector2D displacement);

    void UpdateContaningArea() {m_contaningArea = containingArea();}

    //Call UpdateContaningArea() before calling any of these
    virtual int Left(){return m_contaningArea.left();}
    virtual int Right(){return m_contaningArea.right();}
    virtual int Top(){return m_contaningArea.top();}
    virtual int Bottom(){return m_contaningArea.bottom();}

    DragMode m_dragMode = DragAll;

private:
    //Vector of all the gates within collection
    std::vector<Gate*> m_gates;

    //Number of pixels from border before gates are seen
    const int c_borderBoxMargin = 20;

    QRect containingArea();
    QRect m_contaningArea;
};

#endif // GATECOLLECTION_H

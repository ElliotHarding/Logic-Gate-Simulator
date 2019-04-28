#ifndef GATECOLLECTION_H
#define GATECOLLECTION_H

#include "gate.h"

class GateCollection : public Gate
{
public:
    GateCollection(std::vector<Gate*> m_gates);

    virtual void UpdateOutput() override;
    virtual void UpdateGraphics(QPainter* painter) override;
    virtual Node *GetClickedNode(int clickX, int clickY) override;
    virtual void SaveData(std::ofstream& storage) override;
    virtual bool UpdateDrag(int clickX, int clickY);

private:
    //Vector of all the gates within collection
    std::vector<Gate*> m_gates;

    //Number of pixels from border before gates are seen
    const int c_borderBoxMargin = 10;

    QRect containingArea();
};

#endif // GATECOLLECTION_H

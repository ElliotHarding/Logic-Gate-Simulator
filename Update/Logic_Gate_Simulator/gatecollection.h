#ifndef GATECOLLECTION_H
#define GATECOLLECTION_H

#include "gate.h"

class GateCollection : public Gate
{
public:
    GateCollection(std::vector<Gate*> m_gates, int width, int height);

    virtual void UpdateOutput() override;
    virtual void UpdateGraphics(QPainter* painter) override;
    virtual Node *GetClickedNode(int clickX, int clickY) override;
    virtual void SaveData(std::ofstream& storage);

private:
    std::vector<Gate*> m_gates;
};

#endif // GATECOLLECTION_H

#ifndef GATENOT_H
#define GATENOT_H

#include "gate.h"

class GateNot : public Gate
{
public:
    GateNot();

    virtual void UpdateOutput() override;
    virtual bool UpdateDrag(int clickX, int clickY) override;

    virtual Node *GetClickedNode(int clickX, int clickY) override;

    Node m_input;
    Node m_output;
protected:
    virtual void DrawNodes() override;
};

#endif // GATENOT_H

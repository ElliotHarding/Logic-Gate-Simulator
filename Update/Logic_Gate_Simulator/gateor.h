#ifndef GATEOR_H
#define GATEOR_H

#include "gate.h"

class GateOr : public Gate
{
public:
    GateOr();

    virtual void UpdateOutput() override;
    virtual bool UpdateDrag(int clickX, int clickY) override;

    virtual Node *GetClickedNode(int clickX, int clickY) override;

    Node m_inputA;
    Node m_inputB;
    Node m_output;

protected:
    virtual void DrawNodes() override;
};

#endif // GATEOR_H

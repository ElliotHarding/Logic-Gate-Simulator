#ifndef GATEAND_H
#define GATEAND_H

#include "gate.h"

class GateAnd : public Gate
{
public:
    GateAnd();

    virtual void UpdateOutput() override;
    virtual bool UpdateDrag(int clickX, int clickY) override;

    virtual Node* GetClickedNode(int clickX, int clickY) override;

    Node m_inputA;
    Node m_inputB;
    Node m_output;

protected:
    virtual void DrawNodes() override;
};

#endif // GATEAND_H

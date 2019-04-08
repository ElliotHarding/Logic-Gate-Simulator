#ifndef GATEOR_H
#define GATEOR_H

#include "gate.h"

class GateOr : public Gate
{
public:
    GateOr();

    virtual void UpdateOutput();
    virtual bool UpdateDrag(int clickX, int clickY);

    virtual Node *GetClickedNode(int clickX, int clickY);

    Node m_inputA;
    Node m_inputB;
    Node m_output;
};

#endif // GATEOR_H

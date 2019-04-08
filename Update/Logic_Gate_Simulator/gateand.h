#ifndef GATEAND_H
#define GATEAND_H

#include "gate.h"

class GateAnd : public Gate
{
public:
    GateAnd();

    virtual void UpdateOutput();
    virtual bool UpdateDrag(int clickX, int clickY);

    virtual Node* GetClickedNode(int clickX, int clickY);

    Node m_inputA;
    Node m_inputB;
    Node m_output;
};

#endif // GATEAND_H

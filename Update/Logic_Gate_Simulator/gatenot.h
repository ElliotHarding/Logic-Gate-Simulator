#ifndef GATENOT_H
#define GATENOT_H

#include "gate.h"

class GateNot : public Gate
{
public:
    GateNot();

    virtual void UpdateOutput();
    virtual bool UpdateDrag(int clickX, int clickY);

    virtual Node *GetClickedNode(int clickX, int clickY);

    Node m_input;
    Node m_output;
};

#endif // GATENOT_H

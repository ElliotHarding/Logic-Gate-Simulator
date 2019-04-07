#ifndef GATEAND_H
#define GATEAND_H

#include "gate.h"
#include "node.h"

class GateAnd : public Gate
{
public:
    GateAnd();

    virtual void UpdateOutput();
    virtual void UpdateDrag(int clickX, int clickY);

    Node inputA;
    Node inputB;
    Node output;
};

#endif // GATEAND_H

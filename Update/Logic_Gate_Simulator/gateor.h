#ifndef GATEOR_H
#define GATEOR_H

#include "gate.h"
#include "node.h"

class GateOr : public Gate
{
public:
    GateOr();

    virtual void UpdateOutput();
    virtual void UpdateDrag(int clickX, int clickY);

    Node inputA;
    Node inputB;
    Node output;
};

#endif // GATEOR_H

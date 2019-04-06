#ifndef GATEOR_H
#define GATEOR_H

#include "gate.h"
#include "node.h"

class GateOr : Gate
{
public:
    GateOr(int posX, int posY);

    virtual void UpdateOutput();
    virtual void UpdatePositions(int clickX, int clickY);

    Node inputA;
    Node inputB;
    Node output;
};

#endif // GATEOR_H

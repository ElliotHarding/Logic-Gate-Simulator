#ifndef GATEAND_H
#define GATEAND_H

#include "gate.h"
#include "node.h"

class GateAnd : Gate
{
public:
    GateAnd(int posX, int posY);

    virtual void UpdateOutput();
    virtual void UpdatePositions(int clickX, int clickY);

    Node inputA;
    Node inputB;
    Node output;
};

#endif // GATEAND_H

#ifndef GATENOT_H
#define GATENOT_H

#include "gate.h"
#include "node.h"

class GateNot : Gate
{
public:
    GateNot(int posX, int posY);

    virtual void UpdateOutput();
    virtual void UpdatePositions(int clickX, int clickY);

    Node input;
    Node output;
};

#endif // GATENOT_H

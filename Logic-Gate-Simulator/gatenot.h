#ifndef GATENOT_H
#define GATENOT_H

#include "gate.h"
#include "node.h"

class GateNot : public Gate
{
public:
    GateNot();

    virtual void UpdateOutput();
    virtual void UpdateDrag(int clickX, int clickY);

    Node input;
    Node output;
};

#endif // GATENOT_H

#ifndef GATEAND_H
#define GATEAND_H

#include "gate.h"

class GateAnd : Gate
{
public:
    GateAnd();
    void update(int clickX, int clickY);

    bool inputA;
    bool inputB;
    bool* output = nullptr;
};

#endif // GATEAND_H

#ifndef GATEOR_H
#define GATEOR_H
#include "gate.h"

class GateOr : Gate
{
public:
    GateOr();
    void update(int clickX, int clickY);

    bool inputA;
    bool inputB;
    bool* output = nullptr;
};

#endif // GATEOR_H

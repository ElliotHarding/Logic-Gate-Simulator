#ifndef GATENOT_H
#define GATENOT_H
#include "gate.h"

class GateNot : Gate
{
public:
    GateNot();
    void update(int clickX, int clickY);

    bool inputA;
    bool inputB;
    bool* output = nullptr;
};

#endif // GATENOT_H

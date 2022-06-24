#ifndef GATEXOR_H
#define GATEXOR_H

#include "gateeor.h"

class GateXor : public GateEor
{
public:
    GateXor(const int& x = 0, const int& y = 0, const id& inA = -1, const id& inB = -1, const id& out = -1);

    virtual void UpdateOutput() override;
    virtual Gate* Clone() override;
};

#endif // GATEXOR_H

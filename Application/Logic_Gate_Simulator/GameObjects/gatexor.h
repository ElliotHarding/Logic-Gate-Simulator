#ifndef GATEXOR_H
#define GATEXOR_H

#include "gateeor.h"

class GateXor : public GateEor
{
public:
    GateXor(const int& x, const int& y, const id& inA = idGenerator(), const id& inB = idGenerator(), const id& out = idGenerator());

    virtual void UpdateOutput() override;
    virtual Gate* Clone() override;
};

#endif // GATEXOR_H

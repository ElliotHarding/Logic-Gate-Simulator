#ifndef GATEXOR_H
#define GATEXOR_H

#include "gateeor.h"

class GateXor : public GateEor
{
public:
    GateXor(const int& x = 0, const int& y = 0, const id& inA = idGenerator(), const id& inB = idGenerator(), const id& out = idGenerator());

    virtual void UpdateOutput() override;
    virtual Gate* Clone() override;
};

#endif // GATEXOR_H

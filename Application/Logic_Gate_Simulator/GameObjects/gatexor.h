#ifndef GATEXOR_H
#define GATEXOR_H

#include "gateeor.h"

class GateXor : public GateEor
{
public:
    GateXor();

    virtual void UpdateOutput() override;

    virtual Gate* Clone() override;
};

#endif // GATEXOR_H

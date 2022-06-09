#ifndef GATECONSTANTACTIVE_H
#define GATECONSTANTACTIVE_H

#include "GateSingleOutput.h"

class GateConstantActive : public GateSingleOutput
{
public:
    GateConstantActive(id out = idGenerator());
    ~GateConstantActive();

    virtual void UpdateOutput() override;
    virtual Gate* Clone() override;
};

#endif // GATECONSTANTACTIVE_H

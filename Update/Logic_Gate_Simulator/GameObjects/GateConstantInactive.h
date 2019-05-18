#ifndef GATECONSTANTINACTIVE_H
#define GATECONSTANTINACTIVE_H

#include "GateSingleOutput.h"

class GateConstantInactive : public GateSingleOutput
{
public:
    GateConstantInactive(id out = idGenerator());
    ~GateConstantInactive() override;

    virtual void UpdateOutput() override;
    virtual Gate* Clone() override;
};

#endif // GATECONSTANTINACTIVE_H

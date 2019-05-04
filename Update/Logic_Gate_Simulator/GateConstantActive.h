#ifndef GATECONSTANTACTIVE_H
#define GATECONSTANTACTIVE_H

#include "GateSingleOutput.h"

class GateConstantActive : public GateSingleOutput
{
public:
    GateConstantActive();
    ~GateConstantActive() override;

    virtual void UpdateOutput() override;
};

#endif // GATECONSTANTACTIVE_H

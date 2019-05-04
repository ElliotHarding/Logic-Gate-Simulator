#ifndef GATECONSTANTINACTIVE_H
#define GATECONSTANTINACTIVE_H

#include "GateSingleOutput.h"

class GateConstantInactive : public GateSingleOutput
{
public:
    GateConstantInactive();
    ~GateConstantInactive() override;

    virtual void UpdateOutput() override;
};

#endif // GATECONSTANTINACTIVE_H

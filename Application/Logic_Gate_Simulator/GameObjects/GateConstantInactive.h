#ifndef GATECONSTANTINACTIVE_H
#define GATECONSTANTINACTIVE_H

#include "GateSingleOutput.h"

class GateConstantInactive : public GateSingleOutput
{
public:
    GateConstantInactive(const int& x = 0, const int& y = 0, const id& out = -1);

    virtual void updateOutput() override;
    virtual Gate* clone() override;
};

#endif // GATECONSTANTINACTIVE_H

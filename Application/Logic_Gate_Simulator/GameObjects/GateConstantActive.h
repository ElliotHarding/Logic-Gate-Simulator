#ifndef GATECONSTANTACTIVE_H
#define GATECONSTANTACTIVE_H

#include "GateSingleOutput.h"

class GateConstantActive : public GateSingleOutput
{
public:
    GateConstantActive(const int& x = 0, const int& y = 0, const id& out = idGenerator());

    virtual void UpdateOutput() override;
    virtual Gate* Clone() override;
};

#endif // GATECONSTANTACTIVE_H

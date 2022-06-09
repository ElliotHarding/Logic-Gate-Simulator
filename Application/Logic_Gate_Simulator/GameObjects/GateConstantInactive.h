#ifndef GATECONSTANTINACTIVE_H
#define GATECONSTANTINACTIVE_H

#include "GateSingleOutput.h"

class GateConstantInactive : public GateSingleOutput
{
public:
    GateConstantInactive(const uint& x, const uint& y, QWidget* pParent = nullptr, const id& out = idGenerator());

    virtual void UpdateOutput() override;
    virtual Gate* Clone() override;
};

#endif // GATECONSTANTINACTIVE_H

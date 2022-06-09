#ifndef GATECONSTANTACTIVE_H
#define GATECONSTANTACTIVE_H

#include "GateSingleOutput.h"

class GateConstantActive : public GateSingleOutput
{
public:
    GateConstantActive(const uint& x, const uint& y, QWidget* pParent = nullptr, const id& out = idGenerator());

    virtual void UpdateOutput() override;
    virtual Gate* Clone() override;
};

#endif // GATECONSTANTACTIVE_H

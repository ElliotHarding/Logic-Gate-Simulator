#ifndef GATENAND_H
#define GATENAND_H

#include "gateand.h"

class GateNand : public GateAnd
{
public:
    GateNand();

    virtual void UpdateOutput() override;

    virtual Gate* Clone() override;
};

#endif // GATENAND_H

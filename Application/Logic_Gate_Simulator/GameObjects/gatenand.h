#ifndef GATENAND_H
#define GATENAND_H

#include "gateand.h"

class GateNand : public GateAnd
{
public:
    GateNand(const int& x, const int& y, const id& inA = idGenerator(), const id& inB = idGenerator(), const id& out = idGenerator());

    virtual void UpdateOutput() override;

    virtual Gate* Clone() override;
};

#endif // GATENAND_H

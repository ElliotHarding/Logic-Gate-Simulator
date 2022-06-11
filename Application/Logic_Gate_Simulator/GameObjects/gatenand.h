#ifndef GATENAND_H
#define GATENAND_H

#include "gateand.h"

class GateNand : public GateAnd
{
public:
    GateNand(const int& x = 0, const int& y = 0, const id& inA = idGenerator(), const id& inB = idGenerator(), const id& out = idGenerator());

    virtual void UpdateOutput() override;
    virtual Gate* Clone() override;
};

#endif // GATENAND_H

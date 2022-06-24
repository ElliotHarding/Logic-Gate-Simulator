#ifndef GATENAND_H
#define GATENAND_H

#include "gateand.h"

class GateNand : public GateAnd
{
public:
    GateNand(const int& x = 0, const int& y = 0, const id& inA = -1, const id& inB = -1, const id& out = -1);

    virtual void UpdateOutput() override;
    virtual Gate* Clone() override;
};

#endif // GATENAND_H

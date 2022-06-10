#ifndef GATENOR_H
#define GATENOR_H

#include "gateor.h"

class GateNor : public GateOr
{
public:   
    GateNor(const int& x, const int& y, const id& inA = idGenerator(), const id& inB = idGenerator(), const id& out = idGenerator());

    virtual void UpdateOutput() override;
    virtual Gate* Clone() override;
};

#endif // GATENOR_H

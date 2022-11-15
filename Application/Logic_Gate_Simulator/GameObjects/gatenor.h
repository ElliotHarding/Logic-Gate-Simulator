#ifndef GATENOR_H
#define GATENOR_H

#include "gateor.h"

class GateNor : public GateOr
{
public:   
    GateNor(const int& x = 0, const int& y = 0, const id& inA = -1, const id& inB = -1, const id& out = -1);

    virtual void updateOutput() override;
    virtual Gate* clone() override;
};

#endif // GATENOR_H

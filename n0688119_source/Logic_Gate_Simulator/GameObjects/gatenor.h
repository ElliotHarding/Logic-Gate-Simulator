#ifndef GATENOR_H
#define GATENOR_H

#include "gateor.h"

class GateNor : public GateOr
{
public:   
    GateNor();

    virtual void UpdateOutput() override;
    virtual Gate* Clone() override;
};

#endif // GATENOR_H

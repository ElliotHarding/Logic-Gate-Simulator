#ifndef GATEOUTPUTBOX_H
#define GATEOUTPUTBOX_H

#include "GateSingleOutput.h"

/*
    Recieves input
 */
class GateReciever : public GateSingleOutput
{
public:
    GateReciever();

    virtual void UpdateOutput() override;
};

#endif // GATEOUTPUTBOX_H

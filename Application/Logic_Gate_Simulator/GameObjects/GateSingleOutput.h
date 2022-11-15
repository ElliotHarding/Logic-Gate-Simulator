#ifndef GATESINGLEOUTPUT_H
#define GATESINGLEOUTPUT_H

#include "gate.h"

/*
    Inherited by gates with single output
*/
class GateSingleOutput : public Gate
{
public:
    GateSingleOutput(const int& x, const int& y, const GateType& type, const id& nodeId);

    virtual void updateOutput() override = 0;
    virtual void draw(QPainter& painter) override;

protected:
    Node* m_pOutput;
};

#endif // GATESINGLEOUTPUT_H

#ifndef GATESINGLEOUTPUT_H
#define GATESINGLEOUTPUT_H

#include "gate.h"

#define GateSingleOutputWidth 34
#define GateSingleOutputHeight 34
#define BorderWidth 7

/*
    Inherited by gates with single output
*/
class GateSingleOutput : public Gate
{
public:
    GateSingleOutput(GateType type, id nodeId);

    virtual void UpdateOutput() override = 0;
    virtual void UpdateGraphics(QPainter* painter) override;
    virtual void SetPosition(int x, int y) override;

protected:

    const int NODE_OFFSET_X = GateSingleOutputWidth/2;
    const int NODE_OFFSET_Y = GateSingleOutputHeight/2;
    Node m_output;
};

#endif // GATESINGLEOUTPUT_H

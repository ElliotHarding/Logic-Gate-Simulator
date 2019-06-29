#ifndef GATEOUTPUTBOX_H
#define GATEOUTPUTBOX_H

#include "Gate.h"
#define GateRecieverWidth 24
#define GateRecieverHeight 24

/*
    Recieves input
 */
class GateReciever : public Gate
{
public:
    GateReciever(id out = idGenerator());

    virtual void UpdateOutput() override;
    virtual void UpdateGraphics(QPainter* painter) override;
    virtual void SetPosition(int x, int y) override;
    virtual Gate* Clone() override;

protected:

    const int NODE_OFFSET_X = (GateRecieverWidth/2);
    const int NODE_OFFSET_Y = (GateRecieverHeight/2);
    Node m_input;
};

#endif // GATEOUTPUTBOX_H

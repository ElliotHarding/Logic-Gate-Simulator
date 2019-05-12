#ifndef GATEOUTPUTBOX_H
#define GATEOUTPUTBOX_H

#include "GateSingleOutput.h"

/*
    Recieves input
 */
class GateReciever : public Gate
{
public:
    GateReciever(id out = idGenerator());
    ~GateReciever() override;

    virtual void UpdateOutput() override;
    virtual void UpdateGraphics(QPainter* painter) override;
    virtual void SetPosition(int x, int y) override;

protected:

    const int NODE_OFFSET_X = 25;//GateSingleOutputWidth; //+ (GateSingleOutputWidth/2);
    const int NODE_OFFSET_Y = 25;//GateSingleOutputHeight;
    Node m_input;
};

#endif // GATEOUTPUTBOX_H

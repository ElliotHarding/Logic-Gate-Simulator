#ifndef GATESINGLEOUTPUT_H
#define GATESINGLEOUTPUT_H

#include "gate.h"

#define GateSingleOutputWidth 35
#define GateSingleOutputHeight 35
#define BorderWidth 7

class GateSingleOutput : public Gate
{
public:
    GateSingleOutput(GateType type);
    ~GateSingleOutput() override;

    virtual void UpdateOutput() override = 0;
    virtual void UpdateGraphics(QPainter* painter) override;
    virtual void SetPosition(int x, int y) override;

    virtual Node *GetClickedNode(int clickX, int clickY) override;

    void SaveData(std::ofstream& storage) override;

protected:

    const int NODE_OFFSET_X = GateSingleOutputWidth + (GateSingleOutputWidth/2);
    const int NODE_OFFSET_Y = GateSingleOutputHeight;
    Node m_output;
};

#endif // GATESINGLEOUTPUT_H

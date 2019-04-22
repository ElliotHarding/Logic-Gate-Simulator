#ifndef GATEOUTPUTBOX_H
#define GATEOUTPUTBOX_H

#include "gate.h"
#include <QTimer>

#define GateOutputBoxWidth 35
#define GateOutputBoxHeight 35
#define BorderWidth 7

class GateOutputBox : public Gate
{
public:
    GateOutputBox();
    ~GateOutputBox() override;

    virtual void UpdateOutput() override;
    virtual void UpdateGraphics(QPainter* painter) override;

    virtual Node* GetClickedNode(int clickX, int clickY) override;

protected:

    const int NODE_OFFSET_X = -7;
    const int NODE_OFFSET_Y = GateOutputBoxHeight;
    Node m_input;

    virtual void DrawNodes(QPainter *painter) override;
};

#endif // GATEOUTPUTBOX_H

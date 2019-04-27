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
    virtual void SetPosition(int x, int y) override;
    virtual Node* GetClickedNode(int clickX, int clickY) override;
    virtual void SaveData(std::ofstream& storage) override;

protected:

    const int NODE_OFFSET_X = -7;
    const int NODE_OFFSET_Y = GateOutputBoxHeight;
    Node m_input;
};

#endif // GATEOUTPUTBOX_H

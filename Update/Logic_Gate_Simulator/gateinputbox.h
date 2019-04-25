#ifndef GATEINPUTBOX_H
#define GATEINPUTBOX_H

#include "gate.h"
#include <QTimer>

#define GateInputBoxWidth 35
#define GateInputBoxHeight 35
#define BorderWidth 7

class GateInputBox : public Gate
{
public:
    GateInputBox();
    ~GateInputBox() override;

    virtual void UpdateOutput() override;
    virtual void UpdateGraphics(QPainter* painter) override;
    virtual bool UpdateClicked(int clickX, int clickY) override;

    virtual Node* GetClickedNode(int clickX, int clickY) override;

protected:

    const int NODE_OFFSET_X = GateInputBoxWidth + 17;
    const int NODE_OFFSET_Y = GateInputBoxHeight;
    Node m_output;

    //Toggle functionality
    QTimer m_toggleStateTimer;
    const int c_toggleFrequency = 2;

    virtual void DrawNodes(QPainter *painter) override;
};

#endif // GATEINPUTBOX_H

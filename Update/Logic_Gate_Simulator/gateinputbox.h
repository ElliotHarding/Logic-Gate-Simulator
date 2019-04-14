#ifndef GATEINPUTBOX_H
#define GATEINPUTBOX_H

#include "gate.h"

class GateInputBox : public Gate
{
public:
    GateInputBox();

    virtual void UpdateOutput() override;
    virtual bool UpdateDrag(int clickX, int clickY) override;
    virtual void UpdateGraphics(QPainter* painter) override;

    virtual Node* GetClickedNode(int clickX, int clickY) override;

protected:

    Node m_output;

    bool m_bColorJustSwitched = true;

    //This is the image that shows if the GateInputBox is active, the actual image
    //is still in GameObject class
    QImage m_imageActive;


    virtual void DrawNodes() override;
};

#endif // GATEINPUTBOX_H

#ifndef GATEINPUTBOX_H
#define GATEINPUTBOX_H

#include "gate.h"

class GateInputBox : public Gate
{
public:
    GateInputBox();

    virtual void UpdateOutput() override;
    virtual bool UpdateDrag(int clickX, int clickY) override;

    virtual Node* GetClickedNode(int clickX, int clickY) override;

    Node m_output;

protected:
    bool m_previouslyReleased = true;
    virtual void DrawNodes() override;
};

#endif // GATEINPUTBOX_H

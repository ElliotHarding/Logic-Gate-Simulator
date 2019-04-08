#ifndef GATEINPUTBOX_H
#define GATEINPUTBOX_H

#include "gate.h"

class GateInputBox : public Gate
{
public:
    GateInputBox();

    virtual void UpdateOutput();
    virtual bool UpdateDrag(int clickX, int clickY);

    virtual Node* GetClickedNode(int clickX, int clickY);

    Node m_output;

protected:
    bool m_previouslyReleased = true;
};

#endif // GATEINPUTBOX_H

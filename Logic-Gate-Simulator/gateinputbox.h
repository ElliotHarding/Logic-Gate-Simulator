#ifndef GATEINPUTBOX_H
#define GATEINPUTBOX_H

#include "gate.h"
#include "node.h"

class GateInputBox : public Gate
{
public:
    GateInputBox(int posX, int posY);

    virtual void UpdateOutput();
    virtual void UpdateDrag(int clickX, int clickY);

    Node output;

protected:
    bool m_previouslyReleased = true;
};

#endif // GATEINPUTBOX_H

#include "gateinputbox.h"

GateInputBox::GateInputBox(int posX, int posY) :
    Gate::Gate("iconLocation",posX,posY,10,10),
    output(this)
{
}

void GateInputBox::UpdateOutput()
{
    //if output linked to node, update it and its gate
    if(output.GetLinkedNode())
    {
        output.GetLinkedNode()->value = output.value;
        output.GetLinkedNode()->GetParent()->UpdateOutput();
    }

    Gate::UpdateOutput();
}

void GateInputBox::UpdatePositions(int clickX, int clickY)
{
    //if new click
    if(m_previouslyReleased && pointInside(clickX,clickY))
    {
        output.value = !output.value;
        UpdateOutput();
    }

    m_previouslyReleased = !pointInside(clickX,clickY);

     Gate::UpdatePositions(clickX,clickY);
}

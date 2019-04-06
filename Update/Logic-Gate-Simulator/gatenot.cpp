#include "gatenot.h"

GateNot::GateNot(int posX, int posY) :
    Gate::Gate("iconLocation",posX,posY,10,10),
    input(this),
    output(this)
{
}

void GateNot::UpdateOutput()
{
    bool newVal = !(input.value);
    output.value = newVal;

    //if output linked to node, update it and its gate
    Node* linkedNode = output.GetLinkedNode();
    if(linkedNode)
    {
        linkedNode->value = newVal;
        linkedNode->GetParent()->UpdateOutput();
    }
}

void GateNot::UpdatePositions(int clickX, int clickY)
{
     Gate::UpdatePositions(clickX,clickY);
}

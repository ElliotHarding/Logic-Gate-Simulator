#include "gatenot.h"

GateNot::GateNot() :
    Gate::Gate("iconLocation",10,10),
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

    Gate::UpdateOutput();
}

void GateNot::UpdateDrag(int clickX, int clickY)
{
    Gate::UpdateDrag(clickX, clickY);

    //todo node positions
}

void GateNot::UpdatePositions(int clickX, int clickY)
{
     Gate::UpdatePositions(clickX,clickY);
}

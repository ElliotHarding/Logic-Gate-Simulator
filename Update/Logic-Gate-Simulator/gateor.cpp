#include "gateor.h"

GateOr::GateOr(int posX, int posY) :
    Gate::Gate("iconLocation",posX,posY,10,10),
    inputA(this),
    inputB(this),
    output(this)
{
}

void GateOr::UpdateOutput()
{
    const bool newVal = inputA.value | inputB.value;

    //set output node value
    output.value = newVal;

    //if output linked to node, update it and its gate
    Node* linkedNode = output.GetLinkedNode();
    if(linkedNode)
    {
        //set value of node linked to output node
        linkedNode->value = newVal;

        //update the gate owner of the linked node
        linkedNode->GetParent()->UpdateOutput();
    }
}

void GateOr::UpdatePositions(int clickX, int clickY)
{
     Gate::UpdatePositions(clickX,clickY);
}

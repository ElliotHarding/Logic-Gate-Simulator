#include "gateand.h"

GateAnd::GateAnd(int posX, int posY) :
    Gate::Gate("iconLocation",posX,posY,10,10),
    inputA(this),
    inputB(this),
    output(this)
{

}

void GateAnd::UpdateOutput()
{
    const bool sum = inputA.value & inputB.value;

    //set output node value
    output.value = sum;

    //if output linked to node, update it and its gate
    Node* linkedNode = output.GetLinkedNode();
    if(linkedNode)
    {
        //set value of node linked to output node
        linkedNode->value = sum;

        //update the gate owner of the linked node
        linkedNode->GetParent()->UpdateOutput();
    }
}

void GateAnd::UpdatePositions(int clickX, int clickY)
{
    Gate::UpdatePositions(clickX,clickY);
}

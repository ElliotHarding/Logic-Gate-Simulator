#include "gateor.h"

GateOr::GateOr() :
    Gate::Gate("iconLocation",10,10),
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

    Gate::UpdateOutput();
}

void GateOr::UpdateDrag(int clickX, int clickY)
{
    Gate::UpdateDrag(clickX, clickY);

    //todo node positions
}

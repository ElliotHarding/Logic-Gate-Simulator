#include "gatenot.h"

GateNot::GateNot() :
    Gate::Gate(std::string(":/Resources/gate-not.png").c_str(),10,10),
    m_input(this),
    m_output(this)
{
}

void GateNot::UpdateOutput()
{
    bool newVal = !(m_input.value);
    m_output.value = newVal;

    //if output linked to node;
    //- set value of node linked to output node
    //- update the gate owner of the linked node
    Node* linkedNode = m_output.GetLinkedNode();
    if(linkedNode)
    {
        linkedNode->value = newVal;
        linkedNode->GetParent()->UpdateOutput();
    }

    Gate::UpdateOutput();
}

bool GateNot::UpdateDrag(int clickX, int clickY)
{
    bool returnVal = Gate::UpdateDrag(clickX, clickY);

    //todo node positions

    return returnVal;
}

Node *GateNot::GetClickedNode(int clickX, int clickY)
{
    if( m_input.UpdateClicked(clickX, clickY))
        return &m_input;

    if( m_output.UpdateClicked(clickX, clickY))
        return &m_output;

    return nullptr;
}

void GateNot::DrawNodes()
{

}

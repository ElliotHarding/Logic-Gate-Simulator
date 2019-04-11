#include "gateand.h"

GateAnd::GateAnd() :
    Gate::Gate(std::string(":/Resources/gate-and.png").c_str(),50,50),
    m_inputA(this),
    m_inputB(this),
    m_output(this)
{

}

void GateAnd::UpdateOutput()
{
    const bool sum = m_inputA.value & m_inputB.value;

    //set output node value
    m_output.value = sum;

    //if output linked to node;
    //- set value of node linked to output node
    //- update the gate owner of the linked node
    Node* linkedNode = m_output.GetLinkedNode();
    if(linkedNode)
    {
        linkedNode->value = sum;
        linkedNode->GetParent()->UpdateOutput();
    }

    Gate::UpdateOutput();
}

bool GateAnd::UpdateDrag(int clickX, int clickY)
{
    bool returnVal = Gate::UpdateDrag(clickX, clickY);

    //todo node positions

    return returnVal;
}

Node *GateAnd::GetClickedNode(int clickX, int clickY)
{
    if( m_inputA.UpdateClicked(clickX, clickY))
        return &m_inputA;

    if( m_inputB.UpdateClicked(clickX, clickY))
        return &m_inputB;

    if( m_output.UpdateClicked(clickX, clickY))
        return &m_output;

    return nullptr;
}

void GateAnd::DrawNodes()
{

}

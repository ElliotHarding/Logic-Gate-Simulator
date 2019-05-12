#include "gatenot.h"

GateNot::GateNot(id in, id out) :
    Gate::Gate(GATE_NOT, GateNotWidth,GateNotHeight,std::string(":/Resources/Gates/gate-not.png").c_str()),
    m_input(this,in),
    m_output(this,out)
{
    m_nodes.push_back(&m_input);
    m_nodes.push_back(&m_output);
}

GateNot::~GateNot()
{
    if(m_output.GetLinkedNode())
    {
        m_output.value = 0;
        m_output.GetLinkedNode()->GetParent()->UpdateOutput();
    }

    DetachNodes();
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
    linkedNode = nullptr;
}

void GateNot::SetPosition(int x, int y)
{
    GameObject::SetPosition(x,y);

    m_input.SetPosition(m_layout.x() + M_INPUT_OFFSET_X, m_layout.y() + M_INPUT_OFFSET_Y);
    m_output.SetPosition(m_layout.x() + M_OUTPUT_OFFSET_X, m_layout.y() + M_OUTPUT_OFFSET_Y);
}


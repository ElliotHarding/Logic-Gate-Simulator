#include "gateor.h"

GateOr::GateOr(id inA, id inB, id out) :
    Gate::Gate(GATE_AND, GateOrWidth,GateOrHeight, std::string(":/Resources/Gates/gate-or.png").c_str()),
    m_inputA(this, inA),
    m_inputB(this, inB),
    m_output(this, out)
{
    m_nodes.push_back(&m_inputA);
    m_nodes.push_back(&m_inputB);
    m_nodes.push_back(&m_output);
}

GateOr::~GateOr()
{
    Node* linkedNode = m_output.GetLinkedNode();
    if(linkedNode)
    {
        m_output.value = 0;
        linkedNode->value = 0;
        linkedNode->GetParent()->UpdateOutput();
        linkedNode = nullptr;
    }

    DetachNodes();
}

void GateOr::UpdateOutput()
{
    const bool newVal = m_inputA.value | m_inputB.value;

    //set output node value
    m_output.value = newVal;

    //if output linked to node:
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

void GateOr::SetPosition(int x, int y)
{
    GameObject::SetPosition(x,y);

    m_inputA.SetPosition(m_layout.x() + M_INPUTa_OFFSET_X, m_layout.y() + M_INPUTa_OFFSET_Y);
    m_inputB.SetPosition(m_layout.x() + M_INPUTb_OFFSET_X, m_layout.y() + M_INPUTb_OFFSET_Y);
    m_output.SetPosition(m_layout.x() + M_OUTPUT_OFFSET_X, m_layout.y() + M_OUTPUT_OFFSET_Y);
}

#include "gateand.h"
#include <QDebug>

GateAnd::GateAnd(id inA, id inB, id out) :
    Gate::Gate(GATE_AND, GateAndWidth,GateAndHeight, std::string(":/Resources/Gates/gate-and.png").c_str()),
    m_inputA(this, inA),
    m_inputB(this, inB),
    m_output(this, out)
{
    m_nodes.push_back(&m_inputA);
    m_nodes.push_back(&m_inputB);
    m_nodes.push_back(&m_output);
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
    linkedNode = nullptr;
}

void GateAnd::SetPosition(int x, int y)
{
    GameObject::SetPosition(x,y);

    m_inputA.SetPosition(m_layout.x() + M_INPUTa_OFFSET_X, m_layout.y() + M_INPUTa_OFFSET_Y);
    m_inputB.SetPosition(m_layout.x() + M_INPUTb_OFFSET_X, m_layout.y() + M_INPUTb_OFFSET_Y);
    m_output.SetPosition(m_layout.x() + M_OUTPUT_OFFSET_X, m_layout.y() + M_OUTPUT_OFFSET_Y);
}

Gate *GateAnd::Clone()
{
    GateAnd* clone = new GateAnd();

    //Clone position
    QPoint pos = GetPosition();
    clone->SetPosition(pos.x(), pos.y());

    //Clone nodes
    clone->m_inputA = m_inputA;
    clone->m_inputB = m_inputB;
    clone->m_output = m_output;

    return clone;
}

#include "gateor.h"

GateOr::GateOr(id inA, id inB, id out) :
    Gate::Gate(GATE_OR, GateOrWidth, GateOrHeight, std::string(":/Resources/Gates/gate-or.png").c_str()),
    m_inputA(this, InputNode, inA),
    m_inputB(this, InputNode, inB),
    m_output(this, OutputNode, out)
{
    m_nodes.push_back(&m_inputA);
    m_nodes.push_back(&m_inputB);
    m_nodes.push_back(&m_output);
}

GateOr::GateOr(bool norGate, GateType type, const char* iconLocation, id inA, id inB, id out) :
    Gate::Gate(type, GateOrWidth, GateOrHeight, iconLocation),
    m_inputA(this, InputNode, inA),
    m_inputB(this, InputNode, inB),
    m_output(this, OutputNode, out)
{
    m_nodes.push_back(&m_inputA);
    m_nodes.push_back(&m_inputB);
    m_nodes.push_back(&m_output);
}

void GateOr::UpdateOutput()
{
    const bool newVal = m_pInputA->value() | m_pInputB->value();

    //set output node value
    m_pOutput->setValue(newVal);
}

void GateOr::SetPosition(int x, int y)
{
    GameObject::SetPosition(x,y);

    m_inputA.SetPosition(m_layout.x() + M_INPUTa_OFFSET_X, m_layout.y() + M_INPUTa_OFFSET_Y);
    m_inputB.SetPosition(m_layout.x() + M_INPUTb_OFFSET_X, m_layout.y() + M_INPUTb_OFFSET_Y);
    m_output.SetPosition(m_layout.x() + M_OUTPUT_OFFSET_X, m_layout.y() + M_OUTPUT_OFFSET_Y);
}

Gate *GateOr::Clone()
{
    GateOr* clone = new GateOr();

    //Clone position
    QPoint pos = GetPosition();
    clone->SetPosition(pos.x(), pos.y());

    //Clone nodes
    clone->m_pInputA = m_pInputA;
    clone->m_pInputB = m_pInputB;
    clone->m_pOutput = m_pOutput;

    return clone;
}

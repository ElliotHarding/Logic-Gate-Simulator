#include "gatetrior.h"

GateTriOr::GateTriOr(id inA, id inB, id inC, id out) :
    Gate::Gate(GATE_TRI_OR, GateTriOrWidth, GateTriOrHeight, std::string(":/Resources/Gates/gate-tri-or.png").c_str()),
    m_inputA(this, InputNode, inA),
    m_inputB(this, InputNode, inB),
    m_inputC(this, InputNode, inC),
    m_output(this, OutputNode, out)
{
    m_nodes.push_back(&m_inputA);
    m_nodes.push_back(&m_inputB);
    m_nodes.push_back(&m_inputC);
    m_nodes.push_back(&m_output);
}

void GateTriOr::UpdateOutput()
{
    const bool sum = m_inputA.GetValue() || m_inputB.GetValue() || m_inputC.GetValue();

    //set output node value
    m_output.SetValue(sum);
}

void GateTriOr::SetPosition(int x, int y)
{
    GameObject::SetPosition(x,y);

    m_inputA.SetPosition(m_layout.x() + M_INPUTa_OFFSET_X, m_layout.y() + M_INPUTa_OFFSET_Y);
    m_inputB.SetPosition(m_layout.x() + M_INPUTb_OFFSET_X, m_layout.y() + M_INPUTb_OFFSET_Y);
    m_inputC.SetPosition(m_layout.x() + M_INPUTc_OFFSET_X, m_layout.y() + M_INPUTc_OFFSET_Y);
    m_output.SetPosition(m_layout.x() + M_OUTPUT_OFFSET_X, m_layout.y() + M_OUTPUT_OFFSET_Y);
}

Gate *GateTriOr::Clone()
{
    GateTriOr* clone = new GateTriOr();

    //Clone positions
    QPoint pos = GetPosition();
    clone->SetPosition(pos.x(), pos.y());

    //Clone nodes
    clone->m_inputA = m_inputA;
    clone->m_inputB = m_inputB;
    clone->m_inputC = m_inputC;
    clone->m_output = m_output;

    return clone;
}


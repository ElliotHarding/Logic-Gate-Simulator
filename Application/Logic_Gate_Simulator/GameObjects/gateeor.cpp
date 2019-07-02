#include "gateeor.h"

GateEor::GateEor(id inA, id inB, id out) :
    Gate::Gate(GATE_AND, GateEorWidth,GateEorHeight, std::string(":/Resources/Gates/gate-eor.png").c_str()),
    m_inputA(this, InputNode, inA),
    m_inputB(this, InputNode, inB),
    m_output(this, OutputNode, out)
{
    m_nodes.push_back(&m_inputA);
    m_nodes.push_back(&m_inputB);
    m_nodes.push_back(&m_output);
}

void GateEor::UpdateOutput()
{
    const bool newVal = m_inputA.GetValue() ^ m_inputB.GetValue();

    //set output node value
    m_output.SetValue(newVal);
}

void GateEor::SetPosition(int x, int y)
{
    GameObject::SetPosition(x,y);

    m_inputA.SetPosition(m_layout.x() + M_INPUTa_OFFSET_X, m_layout.y() + M_INPUTa_OFFSET_Y);
    m_inputB.SetPosition(m_layout.x() + M_INPUTb_OFFSET_X, m_layout.y() + M_INPUTb_OFFSET_Y);
    m_output.SetPosition(m_layout.x() + M_OUTPUT_OFFSET_X, m_layout.y() + M_OUTPUT_OFFSET_Y);
}

Gate* GateEor::Clone()
{
    GateEor* clone = new GateEor();

    //Clone position
    QPoint pos = GetPosition();
    clone->SetPosition(pos.x(), pos.y());

    //Clone nodes
    clone->m_inputA = m_inputA;
    clone->m_inputB = m_inputB;
    clone->m_output = m_output;

    return clone;
}

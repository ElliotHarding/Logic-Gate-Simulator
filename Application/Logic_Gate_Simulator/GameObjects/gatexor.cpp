#include "gatexor.h"

GateXor::GateXor() :
    GateEor (1, GATE_XOR, std::string(":/Resources/Gates/gate-neor.png").c_str())
{
}

void GateXor::UpdateOutput()
{
    const bool newVal = !(m_inputA.GetValue() ^ m_inputB.GetValue());

    //set output node value
    m_output.SetValue(newVal);
}

Gate *GateXor::Clone()
{
    GateXor* clone = new GateXor();

    //Clone position
    QPoint pos = GetPosition();
    clone->SetPosition(pos.x(), pos.y());

    //Clone nodes
    clone->m_inputA = m_inputA;
    clone->m_inputB = m_inputB;
    clone->m_output = m_output;

    return clone;
}

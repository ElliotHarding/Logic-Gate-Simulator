#include "gatexor.h"

GateXor::GateXor() :
    GateEor (1, GATE_XOR, std::string(":/Resources/Gates/gate-neor.png").c_str())
{
}

void GateXor::UpdateOutput()
{
    const bool newVal = !(m_pInputA->value() ^ m_pInputB->value());

    //set output node value
    m_pOutput->setValue(newVal);
}

Gate *GateXor::Clone()
{
    GateXor* clone = new GateXor();

    //Clone position
    QPoint pos = GetPosition();
    clone->SetPosition(pos.x(), pos.y());

    //Clone nodes
    clone->m_pInputA = m_pInputA;
    clone->m_pInputB = m_pInputB;
    clone->m_pOutput = m_pOutput;

    return clone;
}

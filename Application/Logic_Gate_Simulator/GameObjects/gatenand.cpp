#include "gatenand.h"

GateNand::GateNand(const int &x, const int &y, const id &inA, const id &inB, const id &out) :
    GateAnd(GATE_NAND, x, y, inA, inB, out, std::string(":/Resources/Gates/gate-nand.png").c_str())
{
}

void GateNand::UpdateOutput()
{
    const bool sum = !(m_pInputA->value() & m_pInputB->value());

    //set output node value
    m_pOutput->setValue(sum);
}

Gate *GateNand::Clone()
{
    GateNand* clone = new GateNand(m_geometry.x(), m_geometry.y(), m_pInputA->id(), m_pInputB->id(), m_pOutput->id());

    //Clone nodes
    clone->m_pInputA = m_pInputA;
    clone->m_pInputB = m_pInputB;
    clone->m_pOutput = m_pOutput;

    return clone;
}

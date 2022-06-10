#include "gatenor.h"

GateNor::GateNor(const int &x, const int &y, const id &inA, const id &inB, const id &out) :
    GateOr(GATE_NOR, x, y, inA, inB, out, std::string(":/Resources/Gates/gate-nor.png").c_str())
{
}

void GateNor::UpdateOutput()
{
    const bool newVal = !(m_pInputA->value() | m_pInputB->value());

    //set output node value
    m_pOutput->setValue(newVal);
}

Gate *GateNor::Clone()
{
    GateNor* clone = new GateNor(m_geometry.x(), m_geometry.y(), m_pInputA->id(), m_pInputB->id(), m_pOutput->id());

    //Clone nodes
    clone->m_pInputA = m_pInputA;
    clone->m_pInputB = m_pInputB;
    clone->m_pOutput = m_pOutput;

    return clone;
}

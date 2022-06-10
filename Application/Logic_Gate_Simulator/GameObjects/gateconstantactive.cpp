#include "GateConstantActive.h"

GateConstantActive::GateConstantActive(const int& x, const int& y, const id& out) :
    GateSingleOutput::GateSingleOutput(x, y, GATE_CONST_ACTIVE, out)
{
    m_pOutput->setValue(1);
}
void GateConstantActive::UpdateOutput()
{
    m_pOutput->setValue(1);
}

Gate *GateConstantActive::Clone()
{
    GateConstantActive* clone = new GateConstantActive(m_geometry.x(), m_geometry.y(), m_pOutput->id());

    //Clone nodes - //Todo : not actually cloning at the moment... just making another pointer
    clone->m_pOutput = m_pOutput;

    return clone;
}

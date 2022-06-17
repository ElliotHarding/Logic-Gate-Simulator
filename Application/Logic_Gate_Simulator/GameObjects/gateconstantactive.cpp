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

    //Clones without the linded nodes... linking comes later.
    clone->m_pOutput->setValue(m_pOutput->value());

    return clone;
}

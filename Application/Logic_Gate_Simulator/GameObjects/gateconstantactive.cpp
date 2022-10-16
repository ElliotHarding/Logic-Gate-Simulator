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
    GateConstantActive* clone = new GateConstantActive(position().x(), position().y(), m_pOutput->id());
    Gate::baseClone(clone);

    return clone;
}

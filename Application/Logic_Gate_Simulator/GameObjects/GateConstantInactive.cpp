#include "GateConstantInactive.h"

GateConstantInactive::GateConstantInactive(const int& x, const int& y, const id& out) :
    GateSingleOutput::GateSingleOutput(x, y, GATE_CONST_INACTIVE, out)
{
    m_pOutput->setValue(0);
}

void GateConstantInactive::updateOutput()
{
    m_pOutput->setValue(0);
}

Gate *GateConstantInactive::clone()
{
    GateConstantInactive* clone = new GateConstantInactive(position().x(), position().y(), m_pOutput->id());
    Gate::baseClone(clone);

    return clone;
}

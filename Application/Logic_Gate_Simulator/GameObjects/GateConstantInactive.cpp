#include "GateConstantInactive.h"

GateConstantInactive::GateConstantInactive(const int& x, const int& y, const id& out) :
    GateSingleOutput::GateSingleOutput(x, y, GATE_CONST_INACTIVE, out)
{
    m_pOutput->setValue(0);
}

void GateConstantInactive::UpdateOutput()
{
    m_pOutput->setValue(0);
}

Gate *GateConstantInactive::Clone()
{
    GateConstantInactive* clone = new GateConstantInactive(m_geometry.x(), m_geometry.y(), m_pOutput->id());
    Gate::baseClone(clone);

    return clone;
}

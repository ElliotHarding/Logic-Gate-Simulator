#include "GateConstantInactive.h"

#include <QWidget>

GateConstantInactive::GateConstantInactive(const uint& x, const uint& y, QWidget* pParent, const id& out) :
    GateSingleOutput::GateSingleOutput(x, y, GATE_CONST_INACTIVE, out, pParent)
{
}

void GateConstantInactive::UpdateOutput()
{
    m_pOutput->setValue(0);
}

Gate *GateConstantInactive::Clone()
{
    GateConstantInactive* clone = new GateConstantInactive(geometry().x(), geometry().y());

    //Clone nodes //Todo : not really cloning atm..
    clone->m_pOutput = m_pOutput;

    return clone;
}

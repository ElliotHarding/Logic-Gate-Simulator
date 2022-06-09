#include "GateConstantActive.h"

GateConstantActive::GateConstantActive(const uint& x, const uint& y, QWidget* pParent, const id& out) :
    GateSingleOutput::GateSingleOutput(x, y, GATE_CONST_ACTIVE, out, pParent)
{
    m_pOutput->setValue(1);
}
void GateConstantActive::UpdateOutput()
{
    m_pOutput->setValue(1);
}

Gate *GateConstantActive::Clone()
{
    GateConstantActive* clone = new GateConstantActive(geometry().x(), geometry().y());

    //Clone nodes
    clone->m_pOutput = m_pOutput;

    return clone;
}

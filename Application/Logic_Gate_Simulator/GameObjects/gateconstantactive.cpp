#include "GateConstantActive.h"

GateConstantActive::GateConstantActive(id out) :
    GateSingleOutput::GateSingleOutput(GATE_CONST_ACTIVE, out)
{
    m_output.SetValue(1);
}

GateConstantActive::~GateConstantActive()
{
}

void GateConstantActive::UpdateOutput()
{
    m_output.SetValue(1);
}

Gate *GateConstantActive::Clone()
{
    GateConstantActive* clone = new GateConstantActive();

    //Clone position
    QPoint pos = GetPosition();
    clone->SetPosition(pos.x(), pos.y());

    //Clone nodes
    clone->m_output = m_output;

    return clone;
}

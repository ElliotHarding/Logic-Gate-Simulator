#include "GateConstantInactive.h"

GateConstantInactive::GateConstantInactive(id out) :
    GateSingleOutput::GateSingleOutput(GATE_CONST_INACTIVE, out)
{
    m_output.SetValue(0);
}

GateConstantInactive::~GateConstantInactive()
{
}

void GateConstantInactive::UpdateOutput()
{
    m_output.SetValue(0);
}

Gate *GateConstantInactive::Clone()
{
    GateConstantInactive* clone = new GateConstantInactive();

    //Clone position
    QPoint pos = GetPosition();
    clone->SetPosition(pos.x(), pos.y());

    //Clone nodes
    clone->m_output = m_output;

    return clone;
}

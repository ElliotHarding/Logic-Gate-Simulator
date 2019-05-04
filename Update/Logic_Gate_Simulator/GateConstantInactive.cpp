#include "GateConstantInactive.h"

GateConstantInactive::GateConstantInactive() :
    GateSingleOutput::GateSingleOutput(GATE_CONST_ACTIVE)
{
    m_output.value = 0;
}

GateConstantInactive::~GateConstantInactive()
{
}

void GateConstantInactive::UpdateOutput()
{
    if(m_output.GetLinkedNode())
        m_output.GetLinkedNode()->value = 0;
}

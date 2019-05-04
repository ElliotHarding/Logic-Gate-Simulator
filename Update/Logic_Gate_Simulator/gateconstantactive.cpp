#include "GateConstantActive.h"

GateConstantActive::GateConstantActive() :
    GateSingleOutput::GateSingleOutput(GATE_CONST_ACTIVE)
{
    m_output.value = 1;
}

GateConstantActive::~GateConstantActive()
{
}

void GateConstantActive::UpdateOutput()
{
    if(m_output.GetLinkedNode())
        m_output.GetLinkedNode()->value = 1;
}

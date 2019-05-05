#include "GateReciever.h"

GateReciever::GateReciever() :
    GateSingleOutput::GateSingleOutput(GATE_RECIEVER)
{
    m_output.value = 0;
}

void GateReciever::UpdateOutput()
{

    if(m_output.GetLinkedNode())
    {
        m_output.value = m_output.GetLinkedNode()->value;
    }

}


#include "GateReciever.h"

GateReciever::GateReciever(id out) :
    GateSingleOutput::GateSingleOutput(GATE_RECIEVER, out)
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


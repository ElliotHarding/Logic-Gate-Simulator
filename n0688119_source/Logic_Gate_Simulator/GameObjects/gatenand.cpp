#include "gatenand.h"

GateNand::GateNand() :
    GateAnd (1, GATE_NAND, std::string(":/Resources/Gates/gate-nand.png").c_str())
{
}


void GateNand::UpdateOutput()
{
    const bool sum = !(m_inputA.GetValue() & m_inputB.GetValue());

    //set output node value
    m_output.SetValue(sum);
}

Gate *GateNand::Clone()
{
    GateNand* clone = new GateNand();

    //Clone position
    QPoint pos = GetPosition();
    clone->SetPosition(pos.x(), pos.y());

    //Clone nodes
    clone->m_inputA = m_inputA;
    clone->m_inputB = m_inputB;
    clone->m_output = m_output;

    return clone;
}

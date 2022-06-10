#include "gatetrieor.h"

GateTriEor::GateTriEor(id inA, id inB, id inC, id out) :
    Gate::Gate(GATE_TRI_EOR, GateTriEorWidth, GateTriEorHeight, std::string(":/Resources/Gates/gate-tri-eor.png").c_str()),
    m_inputA(this, InputNode, inA),
    m_inputB(this, InputNode, inB),
    m_inputC(this, InputNode, inC),
    m_output(this, OutputNode, out)
{
    m_nodes.push_back(m_pInputA);
    m_nodes.push_back(m_pInputB);
    m_nodes.push_back(&m_inputC);
    m_nodes.push_back(m_pOutput);
}

void GateTriEor::UpdateOutput()
{
    const bool sum = m_pInputA->value() ^ m_pInputB->value() ^ m_inputC.GetValue();
    m_output.SetValue(sum);

    if (m_pInputA->value() & m_pInputB->value() & m_inputC.GetValue())
    {

    }
    else
    {

    }
}

void GateTriEor::SetPosition(int x, int y)
{
    GameObject::SetPosition(x,y);

    m_inputA.SetPosition(m_layout.x() + M_INPUTa_OFFSET_X, m_layout.y() + M_INPUTa_OFFSET_Y);
    m_inputB.SetPosition(m_layout.x() + M_INPUTb_OFFSET_X, m_layout.y() + M_INPUTb_OFFSET_Y);
    m_inputC.SetPosition(m_layout.x() + M_INPUTc_OFFSET_X, m_layout.y() + M_INPUTc_OFFSET_Y);
    m_output.SetPosition(m_layout.x() + M_OUTPUT_OFFSET_X, m_layout.y() + M_OUTPUT_OFFSET_Y);
}

Gate *GateTriEor::Clone()
{
    GateTriEor* clone = new GateTriEor();

    //Clone position
    QPoint pos = GetPosition();
    clone->SetPosition(pos.x(), pos.y());

    //Clone nodes
    clone->m_pInputA = m_pInputA;
    clone->m_pInputB = m_pInputB;
    clone->m_inputC = m_inputC;
    clone->m_pOutput = m_pOutput;

    return clone;
}

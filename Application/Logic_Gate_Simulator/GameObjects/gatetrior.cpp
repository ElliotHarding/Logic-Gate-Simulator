#include "gatetrior.h"

GateTriOr::GateTriOr(id inA, id inB, id inC, id out) :
    Gate::Gate(GATE_TRI_OR, GateTriOrWidth, GateTriOrHeight, std::string(":/Resources/Gates/gate-tri-or.png").c_str()),
    m_pInputA(this, InputNode, inA),
    m_pInputB(this, InputNode, inB),
    m_pInputC(this, InputNode, inC),
    m_output(this, OutputNode, out)
{
    m_nodes.push_back(m_pInputA);
    m_nodes.push_back(m_pInputB);
    m_nodes.push_back(&m_pInputC);
    m_nodes.push_back(m_pOutput);
}

void GateTriOr::UpdateOutput()
{
    const bool sum = m_pInputA->value() || m_pInputB->value() || m_pInputC.GetValue();

    //set output node value
    m_pOutput->setValue(sum);
}

void GateTriOr::setPosition(int x, int y)
{
    GameObject::setPosition(x,y);

    m_pInputA.setPosition(m_layout.x() + m_pInputA_OFFSET_X, m_layout.y() + m_pInputA_OFFSET_Y);
    m_pInputB.setPosition(m_layout.x() + m_pInputB_OFFSET_X, m_layout.y() + m_pInputB_OFFSET_Y);
    m_pInputC.setPosition(m_layout.x() + m_pInputC_OFFSET_X, m_layout.y() + m_pInputC_OFFSET_Y);
    m_output.setPosition(m_layout.x() + M_OUTPUT_OFFSET_X, m_layout.y() + M_OUTPUT_OFFSET_Y);
}

Gate *GateTriOr::Clone()
{
    GateTriOr* clone = new GateTriOr();

    //Clone positions
    QPoint pos = position();
    clone->setPosition(pos.x(), pos.y());

    //Clone nodes
    clone->m_pInputA = m_pInputA;
    clone->m_pInputB = m_pInputB;
    clone->m_pInputC = m_pInputC;
    clone->m_pOutput = m_pOutput;

    return clone;
}


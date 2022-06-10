#include "gatetriand.h"
#include <QDebug>

GateTriAnd::GateTriAnd(id inA, id inB, id inC, id out) :
    Gate::Gate(GATE_TRI_AND, GateTriAndWidth,GateTriAndHeight, std::string(":/Resources/Gates/gate-tri-and.png").c_str()),
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

void GateTriAnd::UpdateOutput()
{
    const bool sum = m_pInputA->value() & m_pInputB->value() & m_inputC.GetValue();

    //set output node value
    m_pOutput->setValue(sum);
}

void GateTriAnd::SetPosition(int x, int y)
{
    GameObject::SetPosition(x,y);

    m_inputA.SetPosition(m_layout.x() + M_INPUTa_OFFSET_X, m_layout.y() + M_INPUTa_OFFSET_Y);
    m_inputB.SetPosition(m_layout.x() + M_INPUTb_OFFSET_X, m_layout.y() + M_INPUTb_OFFSET_Y);
    m_inputC.SetPosition(m_layout.x() + M_INPUTc_OFFSET_X, m_layout.y() + M_INPUTc_OFFSET_Y);
    m_output.SetPosition(m_layout.x() + M_OUTPUT_OFFSET_X, m_layout.y() + M_OUTPUT_OFFSET_Y);
}

Gate *GateTriAnd::Clone()
{
    GateTriAnd* clone = new GateTriAnd();

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


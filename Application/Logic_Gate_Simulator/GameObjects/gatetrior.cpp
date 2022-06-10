#include "gatetrior.h"

namespace Settings
{
const uint GateTriOrHeight = 50;
const uint GateTriOrWidth = 100;

const int NodeOffsetX_a = -5;
const int NodeOffsetY_a = (GateTriOrHeight/2) - 11;

const int NodeOffsetX_b = -5;
const int NodeOffsetY_b = GateTriOrHeight/2;

const int NodeOffsetX_c = -5;
const int NodeOffsetY_c = GateTriOrHeight - 13;

const int NodeOffsetX_d = GateTriOrWidth + 5;
const int NodeOffsetY_d = (GateTriOrHeight/2);
}

GateTriOr::GateTriOr(const int &x, const int &y, const id &inA, const id &inB, const id &inC, const id &out) :
    Gate::Gate(GATE_TRI_OR, x, y, Settings::GateTriOrWidth, Settings::GateTriOrHeight, std::string(":/Resources/Gates/gate-tri-or.png").c_str()),
    m_pInputA(new Node(this, Settings::NodeOffsetX_a, Settings::NodeOffsetY_a, InputNode, inA)),
    m_pInputB(new Node(this, Settings::NodeOffsetX_b, Settings::NodeOffsetY_b, InputNode, inB)),
    m_pInputC(new Node(this, Settings::NodeOffsetX_c, Settings::NodeOffsetY_c, InputNode, inC)),
    m_pOutput(new Node(this, Settings::NodeOffsetX_d, Settings::NodeOffsetY_d, OutputNode, out))
{
    m_nodes.push_back(m_pInputA);
    m_nodes.push_back(m_pInputB);
    m_nodes.push_back(m_pInputC);
    m_nodes.push_back(m_pOutput);
}

void GateTriOr::UpdateOutput()
{
    const bool sum = m_pInputA->value() || m_pInputB->value() || m_pInputC->value();

    //set output node value
    m_pOutput->setValue(sum);
}

Gate *GateTriOr::Clone()
{
    GateTriOr* clone = new GateTriOr(m_geometry.x(), m_geometry.y(), m_pInputA->id(), m_pInputB->id(), m_pInputC->id(), m_pOutput->id());

    //Clone nodes
    clone->m_pInputA = m_pInputA;
    clone->m_pInputB = m_pInputB;
    clone->m_pInputC = m_pInputC;
    clone->m_pOutput = m_pOutput;

    return clone;
}


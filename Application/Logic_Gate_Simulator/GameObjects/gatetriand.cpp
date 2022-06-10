#include "gatetriand.h"
#include <QDebug>

namespace Settings
{
const uint GateTriAndHeight = 50;
const uint GateTriAndWidth = 100;

const int NodeOffsetX_a = -55;
const int NodeOffsetY_a = -11;

const int NodeOffsetX_b = -55;
const int NodeOffsetY_b = 0;

const int NodeOffsetX_c = -55;
const int NodeOffsetY_c = 12;

const int NodeOffsetX_d = 55;
const int NodeOffsetY_d = 0;
}

GateTriAnd::GateTriAnd(const int &x, const int &y, const id &inA, const id &inB, const id &inC, const id &out) :
    Gate::Gate(GATE_TRI_AND, x, y, Settings::GateTriAndWidth, Settings::GateTriAndHeight, std::string(":/Resources/Gates/gate-tri-and.png").c_str()),
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

void GateTriAnd::UpdateOutput()
{
    const bool sum = m_pInputA->value() & m_pInputB->value() & m_pInputC->value();

    //set output node value
    m_pOutput->setValue(sum);
}

Gate *GateTriAnd::Clone()
{
    GateTriAnd* clone = new GateTriAnd(m_geometry.x(), m_geometry.y(), m_pInputA->id(), m_pInputB->id(), m_pInputC->id(), m_pOutput->id());

    //Clone nodes
    clone->m_pInputA = m_pInputA;
    clone->m_pInputB = m_pInputB;
    clone->m_pInputC = m_pInputC;
    clone->m_pOutput = m_pOutput;

    return clone;
}


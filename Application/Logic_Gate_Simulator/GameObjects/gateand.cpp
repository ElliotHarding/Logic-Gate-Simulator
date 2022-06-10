#include "gateand.h"
#include <QDebug>

namespace Settings
{
const uint GateAndHeight = 50;
const uint GateAndWidth = 100;

const int NodeOffsetX_a = -5;
const int NodeOffsetY_a = (GateAndHeight/2) - 12;

const int NodeOffsetX_b = -5;
const int NodeOffsetY_b = GateAndHeight - 12;

const int NodeOffsetX_c = GateAndWidth + 5;
const int NodeOffsetY_c = (GateAndHeight/2);
}

GateAnd::GateAnd(const int& x, const int& y, const id& inA, const id& inB, const id& out) :
    Gate(GATE_AND, x, y, Settings::GateAndWidth, Settings::GateAndHeight, std::string(":/Resources/Gates/gate-and.png").c_str()),
    m_pInputA(new Node(this, Settings::NodeOffsetX_a, Settings::NodeOffsetY_a, InputNode, inA)),
    m_pInputB(new Node(this, Settings::NodeOffsetX_b, Settings::NodeOffsetY_b, InputNode, inB)),
    m_pOutput(new Node(this, Settings::NodeOffsetX_c, Settings::NodeOffsetY_c, OutputNode, out))
{
    m_nodes.push_back(m_pInputA);
    m_nodes.push_back(m_pInputB);
    m_nodes.push_back(m_pOutput);
}

GateAnd::GateAnd(const int &x, const int &y, const GateType& type, const id &inA, const id &inB, const id &out, const char *iconLocation) :
    Gate(type, x, y, Settings::GateAndWidth, Settings::GateAndHeight, iconLocation),
    m_pInputA(new Node(this, Settings::NodeOffsetX_a, Settings::NodeOffsetY_a, InputNode, inA)),
    m_pInputB(new Node(this, Settings::NodeOffsetX_b, Settings::NodeOffsetY_b, InputNode, inB)),
    m_pOutput(new Node(this, Settings::NodeOffsetX_c, Settings::NodeOffsetY_c, OutputNode, out))
{
    m_nodes.push_back(m_pInputA);
    m_nodes.push_back(m_pInputB);
    m_nodes.push_back(m_pOutput);
}

void GateAnd::UpdateOutput()
{
    //Perform AND operation on two input nodes
    const bool sum = m_pInputA->value() & m_pInputB->value();

    //set output node value
    m_pOutput->setValue(sum);
}

Gate *GateAnd::Clone()
{
    GateAnd* clone = new GateAnd(m_geometry.x(), m_geometry.y(), m_pInputA->id(), m_pInputB->id(), m_pOutput->id());

    //Clone nodes
    clone->m_pInputA = m_pInputA;
    clone->m_pInputB = m_pInputB;
    clone->m_pOutput = m_pOutput;

    return clone;
}

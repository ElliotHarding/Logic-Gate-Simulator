#include "gatenumberoutput.h"

namespace Settings
{
const uint GateNumberOutputHeight = 50;
const uint GateNumberOutputWidth = 100;

const uint HeightStep (GateNumberOutputHeight/5);

const int NodeOffsetX_a = -50;
const int NodeOffsetY_a = (HeightStep * 1) - 25;

const int NodeOffsetX_b = -50;
const int NodeOffsetY_b = (HeightStep * 2) - 25;

const int NodeOffsetX_c = -50;
const int NodeOffsetY_c = (HeightStep * 3) - 25;

const int NodeOffsetX_d = -50;
const int NodeOffsetY_d = (HeightStep * 4) - 25;

const QFont NumberFont = QFont("Helvetica", 40);
const QFontMetrics NumberFontMetrics(NumberFont);
const uint FontHeightOffset = NumberFontMetrics.height()/4;
}

GateNumberOutput::GateNumberOutput(const int &x, const int &y, const id &inA, const id &inB, const id &inC, const id &inD) :
    Gate::Gate(GATE_NUMBER_OUT, x, y, Settings::GateNumberOutputWidth, Settings::GateNumberOutputHeight, std::string(":/Resources/Gates/gate-number-output.png").c_str()),
    m_pInputA(new Node(this, Settings::NodeOffsetX_a, Settings::NodeOffsetY_a, InputNode, inA)),
    m_pInputB(new Node(this, Settings::NodeOffsetX_b, Settings::NodeOffsetY_b, InputNode, inB)),
    m_pInputC(new Node(this, Settings::NodeOffsetX_c, Settings::NodeOffsetY_c, InputNode, inC)),
    m_pInputD(new Node(this, Settings::NodeOffsetX_d, Settings::NodeOffsetY_d, InputNode, inD)),
    m_output(0)
{
    m_nodes.push_back(m_pInputA);
    m_nodes.push_back(m_pInputB);
    m_nodes.push_back(m_pInputC);
    m_nodes.push_back(m_pInputD);
}

void GateNumberOutput::UpdateOutput()
{
    m_output =   m_pInputA->value() * 1
               + m_pInputB->value() * 2
               + m_pInputC->value() * 4
               + m_pInputD->value() * 8;
}

void GateNumberOutput::draw(QPainter& painter)
{
    Gate::draw(painter);

    painter.setFont(Settings::NumberFont);

    const QPoint textPosition = QPoint(position().x(), position().y() + Settings::FontHeightOffset);
    painter.drawText(textPosition, QString::number(m_output));
}

Gate *GateNumberOutput::Clone()
{
    GateNumberOutput* clone = new GateNumberOutput(m_geometry.x(), m_geometry.y());

    //Clone position
    QPoint pos = position();
    clone->setPosition(pos.x(), pos.y());

    //Clone nodes
    clone->m_pInputA = m_pInputA;
    clone->m_pInputB = m_pInputB;
    clone->m_pInputC = m_pInputC;
    clone->m_pInputD = m_pInputD;

    return clone;
}

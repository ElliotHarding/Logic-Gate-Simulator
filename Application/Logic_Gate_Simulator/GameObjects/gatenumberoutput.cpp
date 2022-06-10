#include "gatenumberoutput.h"
#include <sstream>

GateNumberOutput::GateNumberOutput(id inA, id inB, id inC, id inD) :
    Gate::Gate(GATE_NUMBER_OUT, GateNumberOutputWidth, GateNumberOutputHeight, std::string(":/Resources/Gates/gate-number-output.png").c_str()),
    m_inputA(this, InputNode, inA),
    m_inputB(this, InputNode, inB),
    m_inputC(this, InputNode, inC),
    m_inputD(this, InputNode, inD),
    m_font("Helvetica", 40),
    m_outputText("0")
{
    m_nodes.push_back(m_pInputA);
    m_nodes.push_back(m_pInputB);
    m_nodes.push_back(&m_inputC);
    m_nodes.push_back(&m_inputD);
}

void GateNumberOutput::UpdateOutput()
{
    const int sum =   m_pInputA->value() * 1
                    + m_pInputB->value() * 2
                    + m_inputC.GetValue() * 4
                    + m_inputD.GetValue() * 8;

    std::stringstream stream;
    stream << std::hex << sum;

    m_outputText = QString::fromStdString(stream.str());
}

void GateNumberOutput::setPosition(int x, int y)
{
    GameObject::setPosition(x,y);

    m_inputA.setPosition(m_layout.x() + M_INPUTa_OFFSET_X, m_layout.y() + M_INPUTa_OFFSET_Y);
    m_inputB.setPosition(m_layout.x() + M_INPUTb_OFFSET_X, m_layout.y() + M_INPUTb_OFFSET_Y);
    m_inputC.setPosition(m_layout.x() + M_INPUTc_OFFSET_X, m_layout.y() + M_INPUTc_OFFSET_Y);
    m_inputD.setPosition(m_layout.x() + M_INPUTd_OFFSET_X, m_layout.y() + M_INPUTd_OFFSET_Y);
}

void GateNumberOutput::UpdateGraphics(QPainter *painter)
{
    Gate::UpdateGraphics(painter);

    painter->setFont(m_font);
    const QPoint textPosition = QPoint(position().x() - 6,
                                       m_layout.bottom() - (m_layout.height()/4) + 2);
    painter->drawText(textPosition, m_outputText);
}

Gate *GateNumberOutput::Clone()
{
    GateNumberOutput* clone = new GateNumberOutput();

    //Clone position
    QPoint pos = position();
    clone->setPosition(pos.x(), pos.y());

    //Clone nodes
    clone->m_pInputA = m_pInputA;
    clone->m_pInputB = m_pInputB;
    clone->m_inputC = m_inputC;
    clone->m_inputD = m_inputD;

    return clone;
}

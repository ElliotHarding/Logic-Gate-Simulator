#include "GateReciever.h"

namespace Settings
{
///Dimensions
const uint GateRecieverWidth = 24;
const uint GateRecieverHeight = 24;
const QRect DrawLayout(0, 0, GateRecieverWidth, GateRecieverHeight);

///Node positions
const uint NodeOffsetX = GateRecieverWidth/2;
const uint NodeOffsetY = GateRecieverHeight/2;

///Graphics
const QColor ActiveColor = Qt::red;
const QColor UnActiveColor = Qt::white;
const uint BorderSize = 3;
}

GateReciever::GateReciever(const uint& x, const uint& y, QWidget* pParent, id inputNode) :
    Gate::Gate(pParent, GateType::GATE_RECIEVER, x, y, Settings::GateRecieverWidth, Settings::GateRecieverHeight),
    m_pInput(new Node(this, Settings::NodeOffsetX, Settings::NodeOffsetY, InputNode, inputNode))
{
    m_pInput->setValue(0);
    m_nodes.push_back(m_pInput);
}

void GateReciever::UpdateOutput()
{
}

Gate* GateReciever::Clone()
{
    GateReciever* clone = new GateReciever(geometry().x(), geometry().y());

    //Clone nodes
    clone->m_pInput = m_pInput;

    return clone;
}

void GateReciever::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    //Draw center
    //Fill with red if active
    if(m_pInput->value())
    {
        painter.setPen(QPen(Settings::ActiveColor, Settings::GateRecieverWidth));
        painter.drawEllipse(Settings::DrawLayout);
    }
    else
    {
        painter.setPen(QPen(Settings::UnActiveColor, Settings::GateRecieverWidth));
        painter.drawEllipse(Settings::DrawLayout);
    }

    //Draw border
    painter.setPen(QPen(Qt::lightGray, Settings::BorderSize));
    painter.drawEllipse(Settings::DrawLayout.center(), Settings::GateRecieverWidth, Settings::GateRecieverHeight);
}


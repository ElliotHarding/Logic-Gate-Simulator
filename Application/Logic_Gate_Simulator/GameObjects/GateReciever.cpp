#include "GateReciever.h"

namespace Settings
{
///Dimensions
const uint GateRecieverWidth = 24;
const uint GateRecieverHeight = 24;

///Node positions
const uint NodeOffsetX = GateRecieverWidth/2;
const uint NodeOffsetY = GateRecieverHeight/2;

///Graphics
const QColor ActiveColor = Qt::red;
const QColor UnActiveColor = Qt::white;
const uint BorderSize = 3;
}

GateReciever::GateReciever(const uint& x, const uint& y, const id& inputNode) :
    Gate::Gate(GateType::GATE_RECIEVER, x, y, Settings::GateRecieverWidth, Settings::GateRecieverHeight),
    m_pInput(new Node(this, Settings::NodeOffsetX, Settings::NodeOffsetY, InputNode, inputNode))
{
    m_nodes.push_back(m_pInput);
}

void GateReciever::UpdateOutput()
{
}

Gate* GateReciever::Clone()
{
    GateReciever* clone = new GateReciever(m_geometry.x(), m_geometry.y(), m_pInput->id());

    //Clone nodes //Todo : not actaully cloning atm...
    clone->m_pInput = m_pInput;

    return clone;
}

void GateReciever::draw(QPainter& painter)
{
    //Draw center
    //Fill with red if active
    if(m_pInput->value())
    {
        painter.setPen(QPen(Settings::ActiveColor, Settings::GateRecieverWidth));
        painter.drawEllipse(m_geometry);
    }
    else
    {
        painter.setPen(QPen(Settings::UnActiveColor, Settings::GateRecieverWidth));
        painter.drawEllipse(m_geometry);
    }

    //Draw border
    painter.setPen(QPen(Qt::lightGray, Settings::BorderSize));
    painter.drawEllipse(m_geometry.center(), Settings::GateRecieverWidth, Settings::GateRecieverHeight);
}


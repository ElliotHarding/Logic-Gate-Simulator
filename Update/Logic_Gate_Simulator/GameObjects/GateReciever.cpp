#include "GateReciever.h"

GateReciever::GateReciever(id inputNode) :
    Gate::Gate(GateType::GATE_RECIEVER, GateRecieverWidth, GateRecieverHeight),
    m_input(this, InputNode, inputNode)
{
    m_input.SetValue(0);
    m_nodes.push_back(&m_input);
}

void GateReciever::UpdateOutput()
{
}

void GateReciever::UpdateGraphics(QPainter *painter)
{
    //Paiting variables to be used
    QPainterPath path;
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    //Draw center
    //Fill with red if active
    if(m_input.GetValue())
    {
        brush.setColor(Qt::red);
        painter->setBrush(brush);
        painter->drawEllipse(m_layout);
    }
    else
    {
        brush.setColor(Qt::white);
        painter->setBrush(brush);
        painter->drawEllipse(m_layout.center(), GateRecieverWidth, GateRecieverHeight);
    }

    //Draw border
    QPen pen;
    painter->setPen(pen);
    pen.setColor(Qt::lightGray);
    painter->drawEllipse(m_layout.center(), GateRecieverWidth, GateRecieverHeight);

    //Draw nodes
    m_input.UpdateGraphics(painter);
}

void GateReciever::SetPosition(int x, int y)
{
    GameObject::SetPosition(x,y);

    m_input.SetPosition(m_layout.x() + NODE_OFFSET_X, m_layout.y() + NODE_OFFSET_Y);
}

Gate *GateReciever::Clone()
{
    GateReciever* clone = new GateReciever();

    //Clone position
    QPoint pos = GetPosition();
    clone->SetPosition(pos.x(), pos.y());

    //Clone nodes
    clone->m_input = m_input;

    return clone;
}


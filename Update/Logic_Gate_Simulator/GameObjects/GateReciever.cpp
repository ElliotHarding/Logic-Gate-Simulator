#include "GateReciever.h"

GateReciever::GateReciever(id inputNode) :
    Gate::Gate(GateType::GATE_RECIEVER, GateRecieverWidth, GateRecieverHeight),
    m_input(this, inputNode)
{
    m_input.value = 0;
    m_nodes.push_back(&m_input);
}

void GateReciever::UpdateOutput()
{
    if(m_input.GetLinkedNode())
    {
        m_input.value = m_input.GetLinkedNode()->value;
    }
}

void GateReciever::UpdateGraphics(QPainter *painter)
{
    //Paiting variables to be used
    QPainterPath path;
    QPen pen(Qt::black, 10);

    //Fill with red if active
    if(m_input.value)
    {
        pen.setColor(Qt::red);
        pen.setWidth(22);
        painter->setPen(pen);
        painter->drawEllipse(m_layout);
        pen.setWidth(5);
        painter->drawEllipse(m_layout);
    }

    //Draw border
    pen.setColor(Qt::black);
    pen.setWidth(3);
    painter->setPen(pen);
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


#include "GateReciever.h"

GateReciever::GateReciever(id inputNode) :
    Gate::Gate(GateType::GATE_RECIEVER, GateSingleOutputWidth, GateSingleOutputHeight),
    m_input(this, inputNode)
{
    m_input.value = 0;
    m_nodes.push_back(&m_input);
}

GateReciever::~GateReciever()
{
    m_input.value = 0;
    DetachNodes();
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

    //Draw gate
    painter->setPen(pen);
    painter->drawRect(m_layout);

    //Draw active/inactive buttons
    QRect activeRect = m_layout;
    activeRect.setLeft(activeRect.left() + BorderWidth);
    activeRect.setRight(activeRect.right() - BorderWidth);
    activeRect.setTop(activeRect.top() + BorderWidth);
    activeRect.setBottom(activeRect.bottom() - BorderWidth);

    pen.setColor(m_input.value ? Qt::red : Qt::black);
    pen.setWidth(20);
    painter->setPen(pen);
    painter->drawRect(activeRect);

    //Draw nodes
    m_input.UpdateGraphics(painter);
}

void GateReciever::SetPosition(int x, int y)
{
    GameObject::SetPosition(x,y);

    m_input.SetPosition(m_layout.x() + NODE_OFFSET_X, m_layout.y() + NODE_OFFSET_Y);
}


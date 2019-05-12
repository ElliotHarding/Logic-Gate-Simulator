#include "GateSingleOutput.h"

GateSingleOutput::GateSingleOutput(GateType type, id nodeId) :
    Gate::Gate(type, GateSingleOutputWidth, GateSingleOutputHeight),
    m_output(this, nodeId)
{
    m_nodes.push_back(&m_output);
}

GateSingleOutput::~GateSingleOutput()
{
    Node* linkedNode = m_output.GetLinkedNode();
    if(linkedNode)
    {
        m_output.value = 0;
        linkedNode->value = 0;
        linkedNode->GetParent()->UpdateOutput();
        linkedNode = nullptr;
    }

    DetachNodes();
}

void GateSingleOutput::UpdateGraphics(QPainter *painter)
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

    pen.setColor(m_output.value ? Qt::red : Qt::black);
    pen.setWidth(20);
    painter->setPen(pen);
    painter->drawRect(activeRect);

    //Draw nodes
    m_output.UpdateGraphics(painter);
}

void GateSingleOutput::SetPosition(int x, int y)
{
    GameObject::SetPosition(x,y);

    m_output.SetPosition(m_layout.x() + NODE_OFFSET_X, m_layout.y() + NODE_OFFSET_Y);
}

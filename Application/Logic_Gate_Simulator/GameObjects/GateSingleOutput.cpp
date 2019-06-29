#include "GateSingleOutput.h"

GateSingleOutput::GateSingleOutput(GateType type, id nodeId) :
    Gate::Gate(type, GateSingleOutputWidth, GateSingleOutputHeight),
    m_output(this, OutputNode, nodeId)
{
    m_nodes.push_back(&m_output);
}

void GateSingleOutput::UpdateGraphics(QPainter *painter)
{
    //Draw gate
    painter->setPen(QPen(Qt::lightGray, 10));
    painter->drawRect(m_layout);

    //Draw active/inactive buttons
    QRect activeRect = m_layout;
    activeRect.setLeft(activeRect.left() + BorderWidth);
    activeRect.setRight(activeRect.right() - BorderWidth);
    activeRect.setTop(activeRect.top() + BorderWidth);
    activeRect.setBottom(activeRect.bottom() - BorderWidth);

    painter->setPen(QPen(m_output.GetValue() ? Qt::red : Qt::lightGray, 20));
    painter->drawRect(activeRect);

    //Draw nodes
    m_output.UpdateGraphics(painter);

}

void GateSingleOutput::SetPosition(int x, int y)
{
    GameObject::SetPosition(x,y);

    m_output.SetPosition(m_layout.x() + NODE_OFFSET_X, m_layout.y() + NODE_OFFSET_Y);
}

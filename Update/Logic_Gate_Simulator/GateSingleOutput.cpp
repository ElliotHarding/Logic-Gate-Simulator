#include "GateSingleOutput.h"

GateSingleOutput::GateSingleOutput(GateType type) :
    Gate::Gate(type, GateSingleOutputWidth, GateSingleOutputHeight),
    m_output(this)
{
}

GateSingleOutput::~GateSingleOutput()
{
    DetachNode(&m_output);
}

void GateSingleOutput::UpdateGraphics(QPainter *painter)
{
    //Draw nodes
    m_output.UpdateGraphics(painter);

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
}

void GateSingleOutput::SetPosition(int x, int y)
{
    GameObject::SetPosition(x,y);

    m_output.SetPosition(m_layout.x() + NODE_OFFSET_X, m_layout.y() + NODE_OFFSET_Y);
}

Node *GateSingleOutput::GetClickedNode(int clickX, int clickY)
{
    if( m_output.UpdateClicked(clickX, clickY))
        return &m_output;

    return nullptr;
}

void GateSingleOutput::SaveData(std::ofstream &storage)
{
    //Add general gate info
    Gate::SaveData(storage);

    //Add node information
    m_output.SaveData(storage);

    storage << END_SAVE_TAG_GATE << std::endl;
}

#include "gateinputbox.h"

GateInputBox::GateInputBox() :
    Gate::Gate(GateInputBoxWidth,GateInputBoxHeight),
    m_output(this)
{
    m_type = GateType::GATE_EMMITTER;
    m_toggleStateTimer.start(c_toggleFrequency);
}

GateInputBox::~GateInputBox()
{
    DetachNode(&m_output);
}

void GateInputBox::UpdateOutput()
{
    //if output linked to node;
    //- set value of node linked to output node
    //- update the gate owner of the linked node
    if(m_output.GetLinkedNode())
    {
        m_output.GetLinkedNode()->value = m_output.value; //m_output.value is updated in GateInputBox::UpdateClicked

        //todo setUpdateOutput()
        //m_output.GetLinkedNode()->GetParent()->UpdateOutput();
    }

}

void GateInputBox::UpdateGraphics(QPainter *painter)
{
    //Draw nodes
    m_output.UpdateGraphics(painter);

    //Paiting variables to be used
    QPainterPath path;
    QPen pen(Qt::black, 10);

    //Draw gate
    painter->setPen(pen);
    painter->drawRect(m_layout);

    //Draw active/inactive button
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

bool GateInputBox::UpdateClicked(int clickX, int clickY)
{
    bool isClicked = GameObject::UpdateClicked(clickX,clickY);

    //If being clicked & toggleStateTimer has finished
    //Then toggle output value of gate
    if (isClicked && m_toggleStateTimer.remainingTime() == 0)
    {
        m_toggleStateTimer.stop();
        m_toggleStateTimer.start(c_toggleFrequency);
        m_output.value = !m_output.value;
    }

    return isClicked;
}

void GateInputBox::SetPosition(int x, int y)
{
    GameObject::SetPosition(x,y);

    m_output.SetPosition(m_layout.x() + NODE_OFFSET_X, m_layout.y() + NODE_OFFSET_Y);
}

Node *GateInputBox::GetClickedNode(int clickX, int clickY)
{
    if( m_output.UpdateClicked(clickX, clickY))
        return &m_output;

    return nullptr;
}

void GateInputBox::SaveData(std::ofstream &storage)
{
    //Add general gate info
    Gate::SaveData(storage);

    //Add node information
    m_output.SaveData(storage);

    storage << END_SAVE_TAG_GATE << std::endl;
}


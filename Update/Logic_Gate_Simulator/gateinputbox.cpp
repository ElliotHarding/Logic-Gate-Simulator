#include "gateinputbox.h"

GateInputBox::GateInputBox() :
    Gate::Gate(std::string(":/Resources/box.png").c_str(),10,10),
    m_output(this)
{
}

void GateInputBox::UpdateOutput()
{
    //if new click
    if(m_previouslyReleased && beingClicked)
    {
        m_output.value = !m_output.value;

        //if output linked to node;
        //- set value of node linked to output node
        //- update the gate owner of the linked node
        if(m_output.GetLinkedNode())
        {
            m_output.GetLinkedNode()->value = m_output.value;
            m_output.GetLinkedNode()->GetParent()->UpdateOutput();
        }
    }

    m_previouslyReleased = !beingClicked;

    Gate::UpdateOutput();
}

bool GateInputBox::UpdateDrag(int clickX, int clickY)
{
    bool returnVal = Gate::UpdateDrag(clickX, clickY);

    //todo node positions

    return returnVal;
}

Node *GateInputBox::GetClickedNode(int clickX, int clickY)
{
    if( m_output.UpdateClicked(clickX, clickY))
        return &m_output;

    return nullptr;
}

void GateInputBox::DrawNodes()
{

}


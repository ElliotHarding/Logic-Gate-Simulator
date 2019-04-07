#include "gateinputbox.h"

GateInputBox::GateInputBox() :
    Gate::Gate(std::string("iconLocation").c_str(),10,10),
    output(this)
{
}

void GateInputBox::UpdateOutput()
{
    //if new click
    if(m_previouslyReleased && beingClicked)
    {
        output.value = !output.value;

        //if output linked to node, update it and its gate
        if(output.GetLinkedNode())
        {
            output.GetLinkedNode()->value = output.value;
            output.GetLinkedNode()->GetParent()->UpdateOutput();
        }
    }

    m_previouslyReleased = !beingClicked;

    Gate::UpdateOutput();
}

void GateInputBox::UpdateDrag(int clickX, int clickY)
{
    Gate::UpdateDrag(clickX, clickY);

    //todo node positions
}


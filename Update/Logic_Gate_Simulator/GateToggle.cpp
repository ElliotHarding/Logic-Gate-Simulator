#include "GateToggle.h"

GateToggle::GateToggle() :
    GateSingleOutput::GateSingleOutput(GATE_EMMITTER)
{
    m_toggleStateTimer.start(c_toggleFrequency);
}

GateToggle::~GateToggle()
{
    DetachNode(&m_output);
}

void GateToggle::UpdateOutput()
{
    //if output linked to node;
    //- set value of node linked to output node
    //- update the gate owner of the linked node
    if(m_output.GetLinkedNode())
    {
        m_output.GetLinkedNode()->value = m_output.value; //m_output.value is updated in GateToggle::UpdateClicked

        //todo setUpdateOutput()
        //m_output.GetLinkedNode()->GetParent()->UpdateOutput();
    }

}

bool GateToggle::UpdateClicked(int clickX, int clickY)
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

void GateToggle::SaveData(std::ofstream &storage)
{
    //Add general gate info
    Gate::SaveData(storage);

    //todo save states

    //Add node information
    m_output.SaveData(storage);

    storage << END_SAVE_TAG_GATE << std::endl;
}

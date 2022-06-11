#include "GateToggle.h"
#include "gatefield.h"

namespace Settings
{
///Functionality
const uint MaxToggleFrequencyMs = 2;
}

GateToggle::GateToggle(const int& x, const int& y, const id& out) :
    GateSingleOutput::GateSingleOutput(x, y, GATE_EMMITTER, out)
{
    m_toggleStateTimer.start(Settings::MaxToggleFrequencyMs);
}

void GateToggle::UpdateOutput()
{
    //done in ToggleOutputState & checkClicked
}

GameObject *GateToggle::checkClicked(const QPoint& mouse)
{
    GameObject* pPossibleClickedObject = GameObject::checkClicked(x, y);

    if(pPossibleClickedObject != nullptr && m_pParentField->GetCurrentClickMode() == CLICK_DEFAULT)
    {
        //If being clicked & toggleStateTimer has finished
        //Then toggle output value of gate
        if (m_toggleStateTimer.remainingTime() == 0)
        {
            ToggleOutputState();

            m_pParentField->update();
        }
        return nullptr;
    }

    return pPossibleClickedObject;
}

void GateToggle::ToggleOutputState()
{
    m_toggleStateTimer.stop();
    m_toggleStateTimer.start(Settings::MaxToggleFrequencyMs);
    m_pOutput->setValue(!m_pOutput->value());
}

Gate *GateToggle::Clone()
{
    GateToggle* clone = new GateToggle(m_geometry.x(), m_geometry.y(), m_pOutput->id());

    //Clone nodes - Todo : not actaully cloning....
    clone->m_pOutput = m_pOutput;

    return clone;
}

void GateToggle::SaveData(std::ofstream &storage)
{
    //Add general gate info
    Gate::SaveGeneralData(storage);

    //Add node information
    m_pOutput->SaveData(storage);

    storage << END_SAVE_TAG_GATE << std::endl;
}


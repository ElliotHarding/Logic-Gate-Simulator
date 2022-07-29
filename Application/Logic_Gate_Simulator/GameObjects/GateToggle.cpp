#include "GateToggle.h"
#include "gatefield.h"

GateToggle::GateToggle(const int& x, const int& y, const id& out, const bool& powerState) :
    GateSingleOutput::GateSingleOutput(x, y, GATE_EMMITTER, out)
{
    SetPowerState(powerState);
}

void GateToggle::UpdateOutput()
{
    //done in ToggleOutputState & checkClicked
}

void GateToggle::ToggleOutputState()
{
    m_pOutput->setValue(!m_pOutput->value());
}

Gate *GateToggle::Clone()
{
    GateToggle* clone = new GateToggle(m_geometry.x(), m_geometry.y(), m_pOutput->id());
    Gate::baseClone(clone);

    return clone;
}

void GateToggle::SaveData(QDomDocument& storage, QDomElement& parentElement)
{
    QDomElement gateElement = storage.createElement(Settings::GateElement);

    Gate::SaveGeneralData(gateElement);

    gateElement.setAttribute(Settings::GateTogglePowerStateTag, QString::number(m_pOutput->value()));

    m_pOutput->SaveData(storage, gateElement);

    parentElement.appendChild(gateElement);
}


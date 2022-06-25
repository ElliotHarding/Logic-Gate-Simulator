#include "GateToggle.h"
#include "gatefield.h"

GateToggle::GateToggle(const int& x, const int& y, const id& out) :
    GateSingleOutput::GateSingleOutput(x, y, GATE_EMMITTER, out)
{
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

    //Clones without the linded nodes... linking comes later.
    clone->m_pOutput->setValue(m_pOutput->value());

    return clone;
}

void GateToggle::SaveData(QDomDocument& storage, QDomElement& parentElement)
{
    QDomElement gateElement = storage.createElement("Gate");

    Gate::SaveGeneralData(gateElement);

    gateElement.setAttribute("PowerState", QString::number(m_pOutput->value()));

    m_pOutput->SaveData(storage, gateElement);

    parentElement.appendChild(gateElement);
}


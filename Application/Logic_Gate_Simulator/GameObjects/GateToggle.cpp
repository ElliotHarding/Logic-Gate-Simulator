#include "GateToggle.h"
#include "gatefield.h"

GateToggle::GateToggle(const int& x, const int& y, const id& out, const bool& powerState) :
    GateSingleOutput::GateSingleOutput(x, y, GATE_EMMITTER, out)
{
    setPowerState(powerState);
}

void GateToggle::updateOutput()
{
    //done in toggleOutputState & checkClicked
}

void GateToggle::toggleOutputState()
{
    m_pOutput->setValue(!m_pOutput->value());
}

Gate *GateToggle::clone()
{
    GateToggle* clone = new GateToggle(position().x(), position().y(), m_pOutput->id());
    Gate::baseClone(clone);

    return clone;
}

void GateToggle::saveData(QDomDocument& storage, QDomElement& parentElement)
{
    QDomElement gateElement = storage.createElement(Settings::GateElement);

    Gate::saveGeneralData(storage, gateElement);

    gateElement.setAttribute(Settings::GateTogglePowerStateTag, QString::number(m_pOutput->value()));

    m_pOutput->saveData(storage, gateElement);

    parentElement.appendChild(gateElement);
}


#ifndef GATEINPUTBOX_H
#define GATEINPUTBOX_H

#include "GateSingleOutput.h"
#include <QTimer>

namespace Settings
{
const QString GateTogglePowerStateTag = "PowerState";
}

/*
    Toggles input on/off
 */
class GateToggle : public GateSingleOutput
{
public:
    GateToggle(const int& x = 0, const int& y = 0, const id& out = -1, const bool& powerState = false);

    virtual void updateOutput() override;
    virtual Gate* clone() override;

    void saveData(QDomDocument& storage, QDomElement& parentElement) override;

    ///Power state
    void setPowerState(bool state) {m_pOutput->setValue(state);}
    bool getPowerState() {return m_pOutput->value();}
    void toggleOutputState();
};

#endif // GATEINPUTBOX_H

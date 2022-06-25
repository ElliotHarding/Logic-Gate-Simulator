#ifndef GATEINPUTBOX_H
#define GATEINPUTBOX_H

#include "GateSingleOutput.h"
#include <QTimer>

/*
    Toggles input on/off
 */
class GateToggle : public GateSingleOutput
{
public:
    GateToggle(const int& x = 0, const int& y = 0, const id& out = -1);

    virtual void UpdateOutput() override;
    virtual Gate* Clone() override;

    void SaveData(QDomDocument& storage, QDomElement& parentElement) override;

    ///Power state
    void SetPowerState(bool state) {m_pOutput->setValue(state);}
    bool GetPowerState() {return m_pOutput->value();}
    void ToggleOutputState();
};

#endif // GATEINPUTBOX_H

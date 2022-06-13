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
    GateToggle(const int& x = 0, const int& y = 0, const id& out = idGenerator());

    virtual void UpdateOutput() override;
    virtual Gate* Clone() override;

    void SaveData(std::ofstream& storage) override;

    ///Power state
    void SetPowerState(bool state) {m_pOutput->setValue(state); UpdateOutput();}
    bool GetPowerState() {return m_pOutput->value();}
    void ToggleOutputState();

protected:

    //Toggle functionality
    QTimer m_toggleStateTimer;
};

#endif // GATEINPUTBOX_H

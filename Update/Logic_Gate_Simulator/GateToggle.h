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
    GateToggle(id out = idGenerator());
    ~GateToggle() override;

    virtual void UpdateOutput() override;
    virtual bool UpdateClicked(int clickX, int clickY) override;

    void SaveData(std::ofstream& storage) override;

    bool GetPowerState() {return m_output.value;}
    void ToggleOutputState() {m_output.value = !m_output.value;}

protected:

    //Toggle functionality
    QTimer m_toggleStateTimer;
    const int c_toggleFrequency = 2;
};

#endif // GATEINPUTBOX_H

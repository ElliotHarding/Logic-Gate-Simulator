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

    virtual void UpdateOutput() override;
    virtual bool UpdateClicked(int clickX, int clickY) override;
    virtual void UpdateGraphics(QPainter* painter) override;
    virtual Gate* Clone() override;

    void SaveData(std::ofstream& storage) override;

    //todo check needed
    void SetPowerState(bool state) {m_output.SetValue(state); UpdateOutput();}

    bool GetPowerState() {return m_output.GetValue();}
    void ToggleOutputState();

protected:

    //Toggle functionality
    QTimer m_toggleStateTimer;
    const int c_toggleFrequency = 2;

    const QFont m_font;
};

#endif // GATEINPUTBOX_H

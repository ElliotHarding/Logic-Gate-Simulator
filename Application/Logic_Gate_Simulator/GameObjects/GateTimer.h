#ifndef GATETIMER_H
#define GATETIMER_H

#include "GateSingleOutput.h"
#include <QTimer>

/*
    Toggles input on/off
 */
class GateTimer : public GateSingleOutput
{
public:
    GateTimer(id out = idGenerator());

    virtual void UpdateOutput() override;
    virtual void SaveData(std::ofstream& storage) override;
    virtual void UpdateGraphics(QPainter* painter) override;
    virtual Gate* Clone() override;

    bool CheckTimer();

    void setFrequency(int frequency) {m_frequency = frequency;}
    int getFrequency() {return m_frequency;}

protected:

    //Toggle functionality
    int m_frequency = 500;
    int m_remaningTime;

    const QFont m_font;
};
#endif // GATETIMER_H

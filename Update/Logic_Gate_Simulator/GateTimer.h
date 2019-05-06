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
    GateTimer();

    virtual void UpdateOutput() override;
    virtual void SaveData(std::ofstream& storage) override;

    void setFrequency(int frequency) {m_frequency = frequency;}
    int getFrequency() {return m_frequency;}

protected:

    //Toggle functionality
    QTimer m_timer;
    int m_frequency = 2;
};
#endif // GATETIMER_H

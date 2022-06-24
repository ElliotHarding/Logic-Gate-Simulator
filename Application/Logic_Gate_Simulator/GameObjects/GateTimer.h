#ifndef GATETIMER_H
#define GATETIMER_H

#include "GateSingleOutput.h"
#include <QTimer>

/*
    Toggles input on/off
 */
class GateTimer : public QObject, public GateSingleOutput
{
    Q_OBJECT

public:
    GateTimer(const int& x = 0, const int& y = 0, const id& out = -1);
    ~GateTimer();

    virtual void UpdateOutput() override;
    virtual void SaveData(std::ofstream& storage) override;
    virtual Gate* Clone() override;

    ///Frequency
    void setFrequency(int frequency);
    int getFrequency() {return m_frequency;}

private slots:
    void onTick();

protected:

    int m_frequency = 500;

    QTimer m_timer;
};
#endif // GATETIMER_H

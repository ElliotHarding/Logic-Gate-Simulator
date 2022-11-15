#ifndef GATETIMER_H
#define GATETIMER_H

#include "GateSingleOutput.h"
#include <QTimer>

namespace Settings
{
const QString GateTimerFrequencyTag = "Frequency";
}

/*
    Toggles input on/off
 */
class GateTimer : public QObject, public GateSingleOutput
{
    Q_OBJECT

public:
    GateTimer(const int& x = 0, const int& y = 0, const id& out = -1, const uint& frequency = 500);
    ~GateTimer();

    virtual void updateOutput() override;
    virtual void saveData(QDomDocument& storage, QDomElement& parentElement) override;
    virtual Gate* clone() override;

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

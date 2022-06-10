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
    GateTimer(const int& x, const int& y, const id& out = idGenerator());
    ~GateTimer();

    virtual void UpdateOutput() override;
    virtual void SaveData(std::ofstream& storage) override;
    virtual void draw(QPainter& painter) override;
    virtual Gate* Clone() override;

    ///Frequency
    void setFrequency(int frequency);
    int getFrequency() {return m_frequency;}

private slots:
    void onTick();

protected:

    int m_frequency = 500;

    QTimer* m_pTimer = nullptr;
};
#endif // GATETIMER_H

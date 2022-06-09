#ifndef GATETIMER_H
#define GATETIMER_H

#include "GateSingleOutput.h"
#include <QTimer>

/*
    Toggles input on/off
 */
class GateTimer : public GateSingleOutput, public QObject
{
    Q_OBJECT

public:
    GateTimer(id out = idGenerator());
    ~GateTimer();

    virtual void UpdateOutput() override;
    virtual void SaveData(std::ofstream& storage) override;
    virtual void UpdateGraphics(QPainter* painter) override;
    virtual Gate* Clone() override;

    void setFrequency(int frequency);
    int getFrequency() {return m_frequency;}

private slots:
    void onTick();

protected:

    //Toggle functionality
    int m_frequency = 500;

    QTimer* m_pTimer = nullptr;
};
#endif // GATETIMER_H

#ifndef CIRCUITFROMSCRIPTTHREAD_H
#define CIRCUITFROMSCRIPTTHREAD_H

#include <QThread>

class Circuit;

//////////////////////////////////////////////////////////////////////////
///CircuitFromScriptThread
class CircuitFromScriptThread : public QThread
{
    Q_OBJECT
public:
    CircuitFromScriptThread();

    void setup(const uint& numInputs, uint& numOutputs, const QString& script, const int& maxSeconds, const uint& percentageRandomGate, const uint& maxGates);

    void run();

signals:
    void circuitGenSuccess(Circuit& circuit);
    void circuitGenFailure(const QString& failMessage);

private:
    uint m_numInputs;
    uint m_numOutputs;
    QString m_script;
    int m_maxSeconds;
    uint m_percentageRandomGate;
    uint m_maxGates;
};

#endif // CIRCUITFROMSCRIPTTHREAD_H

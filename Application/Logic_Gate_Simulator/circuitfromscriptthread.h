#ifndef CIRCUITFROMSCRIPTTHREAD_H
#define CIRCUITFROMSCRIPTTHREAD_H

#include "truthtable.h"
#include "circuit.h"

#include <QThread>

class Circuit;

//////////////////////////////////////////////////////////////////////////
///CircuitFromScriptThread
class CircuitFromScriptThread : public QThread
{
    Q_OBJECT
public:
    CircuitFromScriptThread();

    void start(const uint& numInputs, const uint& numOutputs, const QString& script, const int& maxSeconds, const uint& percentageRandomGate, const uint& maxGates);

    void run();

    static TruthTable genTruthTableFromScript(const QString& script, const uint& numInputs, const uint& numOutputs);

signals:
    void circuitGenSuccess(Circuit circuit);
    void circuitGenFailure(const QString& failMessage);

private:
    bool testCircuitAgainstTruthTable(Circuit& circuit, TruthTable& truthTable);
    bool createRandomCircuit(Circuit& circuit, const uint& percentageNewGate, const uint& maxGates);

    uint m_numInputs;
    uint m_numOutputs;
    QString m_script;
    int m_maxSeconds;
    uint m_percentageRandomGate;
    uint m_maxGates;
};

#endif // CIRCUITFROMSCRIPTTHREAD_H

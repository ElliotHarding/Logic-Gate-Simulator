#ifndef CIRCUITFROMSCRIPTTHREAD_H
#define CIRCUITFROMSCRIPTTHREAD_H

#include "truthtable.h"

#include <QThread>

class Circuit;
class GateCollection;

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
    void circuitGenSuccess(GateCollection* pNewCircuit);
    void circuitGenFailure(const QString& failMessage);

private:
    uint m_numInputs;
    uint m_numOutputs;
    QString m_script;
    int m_maxSeconds;
    uint m_percentageRandomGate;
    uint m_maxGates;
};

//////////////////////////////////////////////////////////////////////////
///CircuitFromTruthTableCalculator
class CircuitFromTruthTableThread : public QThread
{
    Q_OBJECT
public:
    CircuitFromTruthTableThread();

    bool start(const TruthTable& truthTable, const int& maxSeconds, const uint& percentageRandomGate, const uint& maxGates);

    void run();

signals:
    void circuitGenSuccess(GateCollection* pNewCircuit);
    void circuitGenFailure(const QString& failMessage);

private:
    TruthTable m_truthTable;
    int m_maxSeconds;
    uint m_percentageRandomGate;
    uint m_maxGates;
};

#endif // CIRCUITFROMSCRIPTTHREAD_H

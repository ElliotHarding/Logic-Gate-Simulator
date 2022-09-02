#ifndef CIRCUITFROMTRUTHTABLETHREAD_H
#define CIRCUITFROMTRUTHTABLETHREAD_H

#include "truthtable.h"
#include "converter.h"

#include <QThread>

class Circuit;
class GateCollection;
class CircuitOptions;

//////////////////////////////////////////////////////////////////////////
///CircuitFromScriptThread
class CircuitFromTruthTableThread : public QThread
{
    Q_OBJECT
public:
    CircuitFromTruthTableThread();

    void start(const TruthTable& truthTable, const CircuitOptions& circuitGenOptions);
    void run();

signals:
    void circuitGenSuccess(GateCollection* pNewCircuit);
    void circuitGenFailure(const QString& failMessage);

private:
    CircuitOptions m_circuitOptions;
    TruthTable m_truthTable;
};

#endif // CIRCUITFROMTRUTHTABLETHREAD_H

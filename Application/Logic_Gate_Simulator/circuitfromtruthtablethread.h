#ifndef CIRCUITFROMTRUTHTABLETHREAD_H
#define CIRCUITFROMTRUTHTABLETHREAD_H

#include "truthtable.h"
#include "converter.h"

#include <QThread>

class Circuit;
class GateCollection;
struct CircuitOptions;

//////////////////////////////////////////////////////////////////////////
///RandomCircuitGenThread
/// This is using the random method! For more see Converter
class RandomCircuitGenThread : public QThread
{
    Q_OBJECT
public:
    RandomCircuitGenThread();

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

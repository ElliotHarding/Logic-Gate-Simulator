#ifndef TRUTHTABLETOBOOLEANEXPRESSIONTHREAD_H
#define TRUTHTABLETOBOOLEANEXPRESSIONTHREAD_H

#include "truthtable.h"
#include "converter.h"

#include <QThread>

//////////////////////////////////////////////////////////////////////////
///RandomCircuitGenThread
/// This is using the random method! For other(better) methods see Converter
class TruthTableToBooleanExpressionsThread : public QThread
{
    Q_OBJECT
public:
    TruthTableToBooleanExpressionsThread();

    void start(const TruthTable& truthTable, const CircuitOptions& circuitGenOptions);
    void run();

signals:
    void expressionsGenSuccess(const std::vector<BooleanExpression> expressions);
    void expressionsGenFailure(const QString& failMessage);

private:
    CircuitOptions m_circuitOptions;
    TruthTable m_truthTable;
};

#endif // TRUTHTABLETOBOOLEANEXPRESSIONTHREAD_H

#ifndef TRUTHTABLETOBOOLEANEXPRESSIONTHREAD_H
#define TRUTHTABLETOBOOLEANEXPRESSIONTHREAD_H

#include "truthtable.h"
#include "converter.h"

#include <QThread>

enum GoalResult
{
    GR_Circuit,
    GR_BooleanExpressions
};

//////////////////////////////////////////////////////////////////////////
///RandomConversionThread
/// This is using the random method! For other(better) methods see Converter
class RandomConversionThread : public QThread
{
    Q_OBJECT
public:
    RandomConversionThread();

    void start(const TruthTable& truthTable, const CircuitOptions& circuitGenOptions, GoalResult goalResult);
    void run();

signals:
    void circuitGenSuccess(GateCollection* pGateCollection);
    void expressionsGenSuccess(const std::vector<BooleanExpression> expressions);
    void generationFailure(const QString& failMessage);

private:
    CircuitOptions m_circuitOptions;
    TruthTable m_truthTable;
    GoalResult m_goalResult;
};

#endif // TRUTHTABLETOBOOLEANEXPRESSIONTHREAD_H

#include "truthtabletobooleanexpressionthread.h"

#include <QRandomGenerator>
#include <cmath>
#include "converter.h"

std::vector<BooleanExpression> createRandomExpressions(const uint& percentageNewGate, const uint& maxGates)
{

}

//////////////////////////////////////////////////////////////////////////
/// \brief CircuitFromScriptThread::CircuitFromScriptThread
///
TruthTableToBooleanExpressionsThread::TruthTableToBooleanExpressionsThread() : QThread()
{
}

void TruthTableToBooleanExpressionsThread::start(const TruthTable& truthTable, const CircuitOptions& circuitGenOptions)
{
    m_truthTable = truthTable;
    m_circuitOptions = circuitGenOptions;

    QThread::start();
}

void TruthTableToBooleanExpressionsThread::run()
{
    const clock_t startTimeMs = clock();

    if(!m_truthTable.isValid())
    {
        emit expressionsGenFailure("Failed to generate. Incorrect format!");
        return;
    }

    const uint iInputs = m_truthTable.inValues[0].size();
    const uint iOutputs = m_truthTable.outValues[0].size();
    if(iInputs == 0 || iOutputs == 0)
    {
        emit expressionsGenFailure("Failed to generate. Incorrect format!");
        return;
    }

    //Begin generating random circuits until one matches truth table
    while(true)
    {
        if((clock() - startTimeMs)/1000 > m_circuitOptions.m_maxSeconds)
        {
            emit expressionsGenFailure("Failed to generate. Ran out of time!");
            return;
        }

        std::vector<BooleanExpression> randomExpressions = createRandomExpressions(m_circuitOptions.m_percentageRandomGate, m_circuitOptions.m_maxGates);

        TruthTable randomTruthTable;
        if(Converter::expressionsToTruthTable(randomExpressions, randomTruthTable) == ConverterResult::SUCCESS)
        {
            if(m_truthTable.outValues == randomTruthTable.outValues)
            {
                emit expressionsGenSuccess(randomExpressions);
                return;
            }
        }
    }
}

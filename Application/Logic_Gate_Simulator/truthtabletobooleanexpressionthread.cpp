#include "truthtabletobooleanexpressionthread.h"

#include <QRandomGenerator>
#include <cmath>
#include "converter.h"

std::vector<BooleanExpression> createRandomExpressions(const std::vector<char>& inputLetters, const std::vector<char>& outputLetters)
{
    std::vector<BooleanExpression> expressions;

    for(const char& outLetter : outputLetters)
    {
        BooleanExpression expression;
        expression.resultLetter = outLetter;

        const uint iRounds = std::floor(QRandomGenerator::global()->generateDouble() * inputLetters.size() + inputLetters.size());
        for(uint i = 0; i < iRounds; i++)
        {
            const bool isOr = expression.letters.size() > 0 && expression.letters[expression.letters.size()-1] != '+' && int(std::floor(QRandomGenerator::global()->generateDouble() * 2)) == 1;
            if(isOr)
            {
                expression.addTerm('+');
                continue;
            }

            const int iRandomInput = std::floor(QRandomGenerator::global()->generateDouble() * inputLetters.size());
            const bool inverted = int(std::floor(QRandomGenerator::global()->generateDouble() * 2)) == 1;
            if(inverted)
            {
                expression.addTerm(inputLetters[iRandomInput], true);
            }
            else
            {
                expression.addTerm(inputLetters[iRandomInput]);
            }
        }

        expressions.push_back(expression);
    }

    return expressions;
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

    //Begin generating random circuits until one matches truth table
    while(true)
    {
        if((clock() - startTimeMs)/1000 > m_circuitOptions.m_maxSeconds)
        {
            emit expressionsGenFailure("Failed to generate. Ran out of time!");
            return;
        }

        std::vector<BooleanExpression> randomExpressions = createRandomExpressions(m_truthTable.inLetters, m_truthTable.outLetters);

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

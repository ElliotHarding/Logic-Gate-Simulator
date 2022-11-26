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

void TruthTableToBooleanExpressionsThread::start(const TruthTable& truthTable, const CircuitOptions& circuitGenOptions, GoalResult goalResult)
{
    m_truthTable = truthTable;
    m_circuitOptions = circuitGenOptions;
    m_goalResult = goalResult;

    QThread::start();
}

void TruthTableToBooleanExpressionsThread::run()
{
    const clock_t startTimeMs = clock();

    if(!m_truthTable.isValid())
    {
        emit generationFailure("Failed to generate. Incorrect format!");
        return;
    }

    //Begin generating random circuits until one matches truth table
    while(true)
    {
        if((clock() - startTimeMs)/1000 > m_circuitOptions.m_maxSeconds)
        {
            emit generationFailure("Failed to generate. Ran out of time!");
            return;
        }

        std::vector<BooleanExpression> randomExpressions = createRandomExpressions(m_truthTable.inLetters, m_truthTable.outLetters);

        TruthTable randomTruthTable;
        if(Converter::expressionsToTruthTable(randomExpressions, randomTruthTable) == ConverterResult::SUCCESS)
        {
            if(m_truthTable.outValues == randomTruthTable.outValues)
            {
                if(m_goalResult == GR_Circuit)
                {
                    GateCollection* pNewCircuit = nullptr;
                    if(Converter::booleanExpressionsToCircuit(randomExpressions, m_circuitOptions, pNewCircuit) != ConverterResult::SUCCESS || pNewCircuit == nullptr)
                    {
                        Logger::log(LogLevel::LL_Error, "TruthTableToBooleanExpressionsThread::run : Generation failed! Converter::booleanExpressionsToCircuit failed.");
                        emit generationFailure("Failed to generate circuit! Check logs.");
                    }
                    else
                    {
                        emit circuitGenSuccess(pNewCircuit);
                    }
                }
                else if(m_goalResult == GR_BooleanExpressions)
                {
                    emit expressionsGenSuccess(randomExpressions);
                }
                else
                {
                    Logger::log(LogLevel::LL_Error, "TruthTableToBooleanExpressionsThread::run - Unknown goal result");
                    emit generationFailure("Internal error. Check logs.");

                }
                return;
            }
        }
    }
}

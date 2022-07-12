#include "truthtable.h"

namespace Settings
{
const uint IntStartAlphabet = 65;
const uint IntEndAlphabet = 122;
}

QString intToBinary(int n)
{
    if ( n == 0 )
    {
        return n+"";
    }

    if (n % 2 == 0)
    {
        return intToBinary(n / 2) + "0";
    }
    else
    {
        return intToBinary(n / 2) + "1";
    }
}

QString setBinaryLen(QString binary, const uint len)
{
    const uint iExtra = len - binary.length();
    for(uint i = 0; i < iExtra; i++)
    {
        binary = "0" + binary;
    }
    return binary;
}

ExpressionCalculatorResult BooleanExpressionCalculator::truthTableToBooleanExpressions(TruthTable& truthTable, std::vector<BooleanExpression>& expressions)
{
    if(truthTable.inValues.size() == 0 || truthTable.outValues.size() == 0)
    {
        return INVALID_TABLE;
    }

    if(expressions.size() != 0)
    {
        return INVALID_INPUT_EXPRESSIONS;
    }

    const uint numOutputs = truthTable.outValues[0].size();
    const uint numRuns = truthTable.inValues.size();

    for(uint iOutput = 0; iOutput < numOutputs; iOutput++)
    {
        BooleanExpression expression;
        expression.resultLetter = char(Settings::IntEndAlphabet-iOutput);

        for(uint iTableRun = 0; iTableRun < numRuns; iTableRun++)
        {
            if(truthTable.outValues[iTableRun][iOutput])
            {
                if(expression.letters.size() != 0)
                {
                    expression.letters.push_back('+');
                    expression.inverted.push_back(false);
                }

                for(uint iInput = 0; iInput < truthTable.inValues[iTableRun].size(); iInput++)
                {
                    if(expression.letters.size() != 0 && iInput != 0)
                    {
                        expression.letters.push_back('.');
                        expression.inverted.push_back(false);
                    }

                    expression.letters.push_back(char(Settings::IntStartAlphabet+iInput));
                    expression.inverted.push_back(!(truthTable.inValues[iTableRun][iInput]));
                }
            }
        }

        expressions.push_back(expression);
    }

    //Todo ~ simplify

    // - Basic rule simplification
    // - Karnaugh maps simplification
    // - Quine-McCluskey algorithm

    const uint numInputs = truthTable.inValues[0].size();

    for(uint iOutput = 0; iOutput < numOutputs; iOutput++)
    {
        std::vector<QString> minTerms;
        for(uint iTableRun = 0; iTableRun < numRuns; iTableRun++)
        {
            if(truthTable.outValues[iTableRun][iOutput])
            {
                minTerms.push_back(setBinaryLen(intToBinary(iTableRun), numInputs));
            }
        }

        std::sort(minTerms.begin(), minTerms.end());
    }

    return SUCESS;
}

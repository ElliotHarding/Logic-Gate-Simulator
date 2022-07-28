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

std::vector<QString> reduceMinTerms(std::vector<QString> minTerms)
{

}

void addTranslatedMinTerm(QString& minTerm, BooleanExpression& expression, std::vector<char>& vars)
{
    const uint minTermSize = minTerm.length() - 1;

    for(uint i = 0; i < minTermSize; i++)
    {
        if(minTerm[i] == '0')
        {
            expression.addTerm(vars[i], true);
        }
        else if(minTerm[i] == '1')
        {
            expression.addTerm(vars[i]);
        }

        expression.addTerm('.');
    }

    if(minTerm[minTermSize] == '0')
    {
        expression.addTerm(vars[minTermSize], true);
    }
    else if(minTerm[minTermSize] == '1')
    {
        expression.addTerm(vars[minTermSize]);
    }
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

    //Todo ~ simplify

    // - Basic rule simplification
    // - Karnaugh maps simplification
    // - Quine-McCluskey algorithm


    const uint numOutputs = truthTable.outValues[0].size();
    const uint numRuns = truthTable.inValues.size();
    const uint numInputs = truthTable.inValues[0].size();

    QString dontCaresMask = "";
    for(uint i = 0; i < numInputs; i++)
    {
        dontCaresMask += "-";
    }

    for(uint iOutput = 0; iOutput < numOutputs; iOutput++)
    {
        BooleanExpression expression;

        std::vector<QString> minTerms;
        for(uint iTableRun = 0; iTableRun < numRuns; iTableRun++)
        {
            if(truthTable.outValues[iTableRun][iOutput])
            {
                minTerms.push_back(setBinaryLen(intToBinary(iTableRun), numInputs));
            }
        }

        std::sort(minTerms.begin(), minTerms.end());

        std::vector<QString> oldMinTerms;
        while(true)
        {
            oldMinTerms = minTerms;
            minTerms = reduceMinTerms(minTerms);

            std::sort(minTerms.begin(), minTerms.end());

            if(oldMinTerms == minTerms)
            {
                break;
            }
        }

        std::vector<char> vars;//Todo ~ gen vars
        const uint minTermsSize = minTerms.size() - 1;
        for(uint iMinTerm = 0; iMinTerm < minTermsSize; iMinTerm++)
        {
            //Todo ~ might need to check minTerms[iMinTerm] != dontCaresMask
            addTranslatedMinTerm(minTerms[iMinTerm], expression, vars);
            expression.addTerm('+');
        }
        addTranslatedMinTerm(minTerms[minTermsSize], expression, vars);

        expressions.push_back(expression);
    }

    return SUCESS;
}

#include "truthtable.h"

namespace Settings
{
const uint IntStartAlphabet = 65;
const uint IntEndAlphabet = 122;
}

bool onlyDiffer1bit(QString& termA, QString& termB)
{
    int iDiffer = 0;

    for(int i = 0; i < termA.length(); i++)
    {
        if(termA[i] != termB[i])
        {
            iDiffer++;
            if(iDiffer > 1)
            {
                return false;
            }
        }
    }

    return iDiffer == 1;
}

// 0010 and 0110 becomes 0-10
QString mergeTerms(const QString& termA, const QString& termB)
{
    QString result = "";

    for(uint i = 0; i < termA.length(); i++)
    {
        if(termA[i] != termB[i])
        {
            result+="-";
        }
        else
        {
            result+=termA[i];
        }
    }

    return result;
}

bool inVector(const std::vector<QString>& vec, const QString& str)
{
    for(uint i = 0; i < vec.size(); i++)
    {
        if(str == vec[i])
        {
            return true;
        }
    }
    return false;
}

std::vector<QString> reduceMinTerms(std::vector<QString> minTerms)
{
    std::vector<QString> newMinTerms;

    const uint minTermsSize = minTerms.size();

    std::vector<bool> checked = std::vector<bool>(minTermsSize, false);

    for(uint i = 0; i < minTermsSize; i++)
    {
        for(uint j = 0; j < minTermsSize; j++)
        {
            if(onlyDiffer1bit(minTerms[i], minTerms[j]))
            {
                checked[i] = true;
                checked[j] = true;

                const QString mergedTerms = mergeTerms(minTerms[i], minTerms[j]);
                if(!inVector(newMinTerms, mergedTerms))
                {
                    newMinTerms.push_back(mergedTerms);
                }
            }
        }
    }

    for(uint i = 0; i < minTermsSize; i++)
    {
        if(!checked[i] && !inVector(newMinTerms, minTerms[i]))
        {
            newMinTerms.push_back(minTerms[i]);
        }
    }

    return newMinTerms;
}

void addTranslatedMinTerm(QString& minTerm, BooleanExpression& expression, std::vector<char>& vars)
{
    const uint minTermSize = minTerm.length() - 1;

    for(uint i = 0; i < minTermSize; i++)
    {
        if(minTerm[i] != "-")
        {
            if(minTerm[i] == '0')
            {
                expression.addTerm(vars[i], true);
            }
            else if(minTerm[i] == '1')
            {
                expression.addTerm(vars[i]);
            }
        }
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

    std::vector<char> vars;
    for(uint i = 0; i < numInputs; i++)
    {
        vars.push_back(char(Settings::IntStartAlphabet + i));
    }

    for(uint iOutput = 0; iOutput < numOutputs; iOutput++)
    {
        BooleanExpression expression;
        expression.resultLetter = Settings::IntEndAlphabet - iOutput;

        //Get min terms
        std::vector<QString> minTerms;
        for(uint iTableRun = 0; iTableRun < numRuns; iTableRun++)
        {
            if(truthTable.outValues[iTableRun][iOutput])
            {
                QString minTerm = "";
                for(const bool input : truthTable.inValues[iTableRun])
                {
                    minTerm += (input ? "1" : "0");
                }
                minTerms.push_back(minTerm);
            }
        }

        //Reduce min terms
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

        //Translate reduced min terms into boolean expression
        const uint minTermsSize = minTerms.size() - 1;
        for(uint iMinTerm = 0; iMinTerm < minTermsSize; iMinTerm++)
        {
            //Todo ~ might need to check minTerms[iMinTerm] != dontCaresMask
            addTranslatedMinTerm(minTerms[iMinTerm], expression, vars);
            expression.addTerm('+');
        }
        addTranslatedMinTerm(minTerms[minTermsSize], expression, vars);

        //Finish
        expressions.push_back(expression);
    }

    return SUCESS;
}

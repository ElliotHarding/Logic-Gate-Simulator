#ifndef TRUTHTABLE_H
#define TRUTHTABLE_H

#include <vector>
#include <QString>

struct TruthTable
{
    std::vector<std::vector<bool>> inValues;
    std::vector<std::vector<bool>> outValues;
    unsigned int size;

    std::vector<bool> genInputs(const unsigned int& iTableRun, const unsigned int& numInputs)
    {
        std::vector<bool> inputs;
        int mask = 1;
        for(unsigned int i = 0; i < numInputs; i++)
        {
            if((mask&iTableRun) >= 1)
                inputs.push_back(true);
            else
                inputs.push_back(false);
            mask<<=1;
        }
        return inputs;
    }
};

struct BooleanExpression
{
    std::vector<char> letters;
    std::vector<bool> inverted;
    char resultLetter;

    void addTerm(const char& letter, const bool& bInverted = false)
    {
        letters.push_back(letter);
        inverted.push_back(bInverted);
    }

    QString lettersAsString()
    {
        QString result = "";

        for(uint i = 0; i < letters.size(); i++)
        {
            result += letters[i];
        }

        return result;
    }
};

enum ExpressionCalculatorResult
{
    SUCCESS,
    INVALID_TABLE,
    INVALID_INPUT_EXPRESSIONS
};

class BooleanExpressionCalculator
{
public:
    static ExpressionCalculatorResult truthTableToBooleanExpressions(TruthTable& truthTable, std::vector<BooleanExpression>& expressions);
    static ExpressionCalculatorResult expressionsToTruthTable(std::vector<BooleanExpression>& expressions, TruthTable& truthTable);
};

#endif // TRUTHTABLE_H

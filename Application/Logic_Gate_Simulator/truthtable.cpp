#include "truthtable.h"

std::vector<bool> TruthTable::genInputs(const unsigned int &iTableRun, const unsigned int &numInputs)
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

void BooleanExpression::addTerm(const char &letter, const bool &bInverted)
{
    letters.push_back(letter);
    inverted.push_back(bInverted);
}

QString BooleanExpression::lettersAsString()
{
    QString result = "";

    for(uint i = 0; i < letters.size(); i++)
    {
        result += letters[i];
    }

    return result;
}

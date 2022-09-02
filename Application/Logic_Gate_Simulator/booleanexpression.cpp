#include "booleanexpression.h"

void BooleanExpression::addTerm(const char& letter, const bool& bInverted)
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

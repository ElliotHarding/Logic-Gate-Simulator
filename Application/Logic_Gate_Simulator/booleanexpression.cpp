#include "booleanexpression.h"

void BooleanExpression::addTerm(const char &letter, const bool &bInverted)
{
    if(bInverted)
    {
        letters.push_back('!');
    }
    letters.push_back(letter);
}

bool BooleanExpression::isInverted(uint iLetter) const
{
    if(iLetter > 0 && iLetter <= letters.size() && letters[iLetter-1] == '!')
    {
        return true;
    }
    return false;
}

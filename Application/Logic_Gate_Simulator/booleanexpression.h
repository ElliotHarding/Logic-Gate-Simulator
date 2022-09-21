#ifndef BOOLEANEXPRESSION_H
#define BOOLEANEXPRESSION_H

#include <vector>
#include <QString>

struct BooleanExpression
{
    std::vector<char> letters;
    char resultLetter;

    void addTerm(const char& letter, const bool& bInverted = false);
    bool isInverted(uint iLetter) const;
};

#endif // BOOLEANEXPRESSION_H

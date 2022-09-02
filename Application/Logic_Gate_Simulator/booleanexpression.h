#ifndef BOOLEANEXPRESSION_H
#define BOOLEANEXPRESSION_H

#include <vector>
#include <QString>

struct BooleanExpression
{
    std::vector<char> letters;
    std::vector<bool> inverted;
    char resultLetter;

    void addTerm(const char& letter, const bool& bInverted = false);

    QString lettersAsString();
};

#endif // BOOLEANEXPRESSION_H

#ifndef TRUTHTABLE_H
#define TRUTHTABLE_H

#include <vector>
#include <QString>

struct TruthTable
{
    std::vector<std::vector<bool>> inValues;
    std::vector<std::vector<bool>> outValues;
    unsigned int size = 0;

    std::vector<bool> genInputs(const unsigned int& iTableRun, const unsigned int& numInputs);
};

struct BooleanExpression
{
    std::vector<char> letters;
    std::vector<bool> inverted;
    char resultLetter;

    void addTerm(const char& letter, const bool& bInverted = false);

    QString lettersAsString();
};

#endif // TRUTHTABLE_H

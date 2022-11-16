#ifndef TRUTHTABLE_H
#define TRUTHTABLE_H

#include <vector>
#include <QString>

struct TruthTable
{
    std::vector<char> inLetters;
    std::vector<char> outLetters;
    std::vector<std::vector<bool>> inValues;
    std::vector<std::vector<bool>> outValues;
    unsigned int size = 0;

    std::vector<bool> genInputs(const unsigned int& iTableRun, const unsigned int& numInputs);
    bool isEmptyTable();
};

#endif // TRUTHTABLE_H

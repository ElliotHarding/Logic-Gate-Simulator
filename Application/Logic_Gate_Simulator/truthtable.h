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

    void genInputs(const unsigned int& numInputs);
    static std::vector<bool> genInputValues(const unsigned int& iTableRun, const unsigned int& numInputs);
    bool isEmptyTable();
    bool isValid();

    bool inInputs(const char newLetter);
    bool inOutputs(const char newLetter);

    void addInputLetters(const uint iNewLetters);
    void addOutputLetters(const uint iNewLetters);
};

#endif // TRUTHTABLE_H

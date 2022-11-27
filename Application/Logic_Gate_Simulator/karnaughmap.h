#ifndef KARNAUGHMAP_H
#define KARNAUGHMAP_H

#include <vector>
#include "truthtable.h"

struct KarnaughMap
{
    std::vector<char> inputLetters;
    char outputLetter;

    std::vector<std::pair<char, bool>> xInputs;//top axis
    std::vector<std::pair<char, bool>> yInputs;//left axis
    std::vector<std::vector<bool>> values;

    bool init(const std::vector<char>& inputLetters, const char& outputLetter);
    bool initFromTruthTable(const TruthTable& tt, const int& iOutput);
};

#endif // KARNAUGHMAP_H

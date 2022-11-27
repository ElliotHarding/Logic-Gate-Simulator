#ifndef KARNAUGHMAP_H
#define KARNAUGHMAP_H

#include <vector>

struct KarnaughMap
{
    std::vector<char> inputLetters;
    char outputLetter;

    std::vector<std::pair<char, bool>> xInputs;//top axis
    std::vector<std::pair<char, bool>> yInputs;//left axis
    std::vector<std::vector<bool>> values;

    bool init(std::vector<char> inputLetters);
};

#endif // KARNAUGHMAP_H

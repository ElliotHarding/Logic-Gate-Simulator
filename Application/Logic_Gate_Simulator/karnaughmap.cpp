#include "karnaughmap.h"
#include <cmath>
#include "truthtable.h"

bool KarnaughMap::init(const std::vector<char>& inLetters, const char& cOutputLetter)
{
    outputLetter = cOutputLetter;
    inputLetters = inLetters;
    const int numInputLetters = inputLetters.size();
    const int xInputsCount = std::floor(numInputLetters / 2);
    const int count = pow(2, numInputLetters);



    return true;
}

bool KarnaughMap::initFromTruthTable(const TruthTable& tt, const int& iOutput)
{
    if(tt.inLetters.size() == 0 || tt.outLetters.size() == 0 || tt.size == 0 || tt.inValues.size() == 0 || tt.inValues[0].size() == 0 || tt.outValues.size() == 0 || tt.outValues[0].size() == 0)
    {
        return false;
    }

    inputLetters = tt.inLetters;
    outputLetter = tt.outLetters[iOutput];

    const int numInputLetters = inputLetters.size();
    const int xInputsCount = std::floor(numInputLetters / 2);


    return true;
}

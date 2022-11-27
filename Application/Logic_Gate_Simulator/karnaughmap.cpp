#include "karnaughmap.h"
#include <cmath>
#include "truthtable.h"

bool KarnaughMap::init(const std::vector<char>& inLetters, const char& cOutputLetter)
{
    outputLetter = cOutputLetter;
    inputLetters = inLetters;
    const int numInputLetters = inputLetters.size();
    const int xInputsCount = std::floor(numInputLetters / 2);
    const int yInputsCount = inputLetters.size() - xInputsCount;

    const int xRowLen = pow(2, xInputsCount);
    const int yColLen = pow(2, yInputsCount);

    for(int x = 0; x < xRowLen; x++)
    {
        std::vector<std::pair<char, bool>> colInputs;
        std::vector<bool> inValues = TruthTable::genInputValues(x, xInputsCount);
        for(int iInput = 0; iInput < inValues.size(); iInput++)
        {
            std::pair<char, bool> colInput(inLetters[iInput], inValues[iInput]);
            colInputs.push_back(colInput);
        }
        xInputs.push_back(colInputs);
    }

    for(int y = 0; y < yColLen; y++)
    {
        std::vector<std::pair<char, bool>> rowInputs;
        std::vector<bool> inValues = TruthTable::genInputValues(y, xInputsCount);
        for(int iInput = 0; iInput < inValues.size(); iInput++)
        {
            std::pair<char, bool> rowInput(inLetters[iInput+xInputsCount], inValues[iInput]);
            rowInputs.push_back(rowInput);
        }
        yInputs.push_back(rowInputs);
    }


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

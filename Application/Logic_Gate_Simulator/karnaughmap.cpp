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

    //Generate input values
    for (int iRun = 0; iRun < count; iRun++)
    {
        std::vector<bool> inputValues = TruthTable::genInputValues(iRun, numInputLetters);
        for(int iInputValue = 0; iInputValue < numInputLetters; iInputValue++)
        {
            std::pair<char, bool> input(inputLetters[iInputValue], inputValues[iInputValue]);
            if(iInputValue < xInputsCount)
            {
                xInputs.push_back(input);
            }
            else
            {
                yInputs.push_back(input);
            }
        }
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

    //Generate input values
    for (int iRun = 0; iRun < tt.size; iRun++)
    {
        for(int iInputValue = 0; iInputValue < numInputLetters; iInputValue++)
        {
            std::pair<char, bool> input(inputLetters[iInputValue], tt.inValues[iRun][iInputValue]);
            if(iInputValue < xInputsCount)
            {
                xInputs.push_back(input);
            }
            else
            {
                yInputs.push_back(input);
            }
        }
        values.push_back(tt.outValues[iRun]);
    }

    return true;
}

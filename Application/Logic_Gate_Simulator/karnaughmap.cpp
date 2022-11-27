#include "karnaughmap.h"
#include <cmath>
#include "truthtable.h"

bool KarnaughMap::init(std::vector<char> inputLetters)
{
    const int numInputLetters = inputLetters.size();
    const int xInputsCount = std::floor(numInputLetters / 2);
    const int count = pow(2, numInputLetters);

    //Generate input values
    TruthTable temp;
    for (int iRun = 0; iRun < count; iRun++)
    {
        std::vector<bool> inputValues = temp.genInputs(iRun, numInputLetters);
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
}

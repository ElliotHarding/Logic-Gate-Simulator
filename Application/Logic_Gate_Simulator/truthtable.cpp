#include "truthtable.h"

std::vector<bool> TruthTable::genInputs(const unsigned int &iTableRun, const unsigned int &numInputs)
{
    std::vector<bool> inputs;
    int mask = 1;
    for(unsigned int i = 0; i < numInputs; i++)
    {
        if((mask&iTableRun) >= 1)
            inputs.push_back(true);
        else
            inputs.push_back(false);
        mask<<=1;
    }
    return inputs;
}

bool TruthTable::isEmptyTable()
{
    if(inValues.size() != 0 || outValues.size() != 0 || size != 0 || inLetters.size() != 0 || outLetters.size() != 0)
    {
        return false;
    }
    return true;
}

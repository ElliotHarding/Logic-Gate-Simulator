#ifndef TRUTHTABLE_H
#define TRUTHTABLE_H

#include <vector>

struct TruthTable
{
    std::vector<std::vector<bool>> inValues;
    std::vector<std::vector<bool>> outValues;
    unsigned int size;
};

std::vector<bool> genInputs(const unsigned int& iTableRun, const unsigned int& numInputs)
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

#endif // TRUTHTABLE_H

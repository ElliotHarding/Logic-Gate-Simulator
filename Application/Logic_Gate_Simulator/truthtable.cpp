#include "truthtable.h"

void TruthTable::genInputs(const unsigned int& numInputs)
{
    inValues.clear();
    size = pow(2, numInputs);

    for (uint iTableRun = 0; iTableRun < size; iTableRun++)
    {
        inValues.push_back(genInputValues(iTableRun, numInputs));
    }
}

std::vector<bool> TruthTable::genInputValues(const unsigned int &iTableRun, const unsigned int &numInputs)
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

bool TruthTable::isValid()
{
    if(inValues.empty() || outValues.empty() || inLetters.empty() || outLetters.empty() || size == 0)
    {
        return false;
    }
    return true;
}

bool inVector(const std::vector<char>& vec, const char& chr)
{
    for(uint i = 0; i < vec.size(); i++)
    {
        if(chr == vec[i])
        {
            return true;
        }
    }
    return false;
}

bool TruthTable::inInputs(const char newLetter)
{
    return inVector(inLetters, newLetter);
}

bool TruthTable::inOutputs(const char newLetter)
{
    return inVector(outLetters, newLetter);
}

void TruthTable::addInputLetters(const uint iNewLetters)
{
    for(int i = 0; i < iNewLetters; i++)
    {
        char newLetter = 'A';
        while(inInputs(newLetter))
        {
            newLetter++;
        }
        inLetters.push_back(newLetter);
    }
}

void TruthTable::addOutputLetters(const uint iNewLetters)
{
    for(int i = 0; i < iNewLetters; i++)
    {
        char newLetter = 'Z';
        while(inOutputs(newLetter))
        {
            newLetter--;
        }
        outLetters.push_back(newLetter);
    }
}



#ifndef KARNAUGHMAP_H
#define KARNAUGHMAP_H

#include <vector>
#include "truthtable.h"

struct KarnaughMap
{
    std::vector<char> inputLetters;
    char outputLetter;

    std::vector<std::vector<std::pair<char, bool>>> xInputs;//top axis
    std::vector<std::vector<std::pair<char, bool>>> yInputs;//left axis
    std::vector<std::vector<bool>> values;

    bool init(const std::vector<char>& inputLetters, const char& outputLetter);
    bool initFromTruthTable(const TruthTable& tt, const int& iOutput);
};

struct SpillProofValues
{
    int width;
    int height;

    std::vector<std::vector<bool>> values;

    bool getValue(const int& x, const int& y)
    {
        int newX, newY;
        wrapRound(x, newX, y, newY);

        return values[newX][newY];
    }

    void setValue(const int& x, const int& y, const bool& value)
    {
        int newX, newY;
        wrapRound(x, newX, y, newY);

        values[newX][newY] = value;
    }

    void wrapRound(const int& x, int& newX, const int& y, int& newY)
    {
        newX = x;
        if(x < 0)
        {
            newX = width - x;
        }
        else if(x >= width)
        {
            newX = x - width;
        }

        newY = y;
        if(y < 0)
        {
            newY = height - y;
        }
        else if(y >= height)
        {
            newY = y - height;
        }
    }
};

#endif // KARNAUGHMAP_H

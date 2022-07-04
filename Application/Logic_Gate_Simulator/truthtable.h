#ifndef TRUTHTABLE_H
#define TRUTHTABLE_H

#include <vector>

struct TruthTable
{
    std::vector<std::vector<bool>> inValues;
    std::vector<std::vector<bool>> outValues;
    unsigned int size;
};

#endif // TRUTHTABLE_H

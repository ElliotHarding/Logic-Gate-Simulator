#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <vector>
#include <map>
#include "gatecollection.h"
#include "GateToggle.h"
#include "GateReciever.h"

//////////////////////////////////////////////////////////////////////////
///Circuit
class Circuit
{
public:
    Circuit(const std::vector<char>& inputLetters, const std::vector<char>& outputLetters);
    ~Circuit();

    GateCollection* createGateCollection();
    void deleteMainGates();

    std::vector<Gate*> mainGates;
    std::map<char, GateToggle*> inputs;
    std::map<char, GateReciever*> outputs;
private:
    bool m_bDeleteGates = true; //Delete gates on destructor
};

#endif // CIRCUIT_H

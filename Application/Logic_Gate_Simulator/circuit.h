#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <vector>

class Gate;
class GateCollection;
class GateToggle;
class GateReciever;

//////////////////////////////////////////////////////////////////////////
///Circuit
class Circuit
{
public:
    Circuit(const unsigned int& inputs, const unsigned int& outputs);
    ~Circuit();

    GateCollection* createGateCollection();
    void deleteMainGates();

    std::vector<Gate*> mainGates;
    std::vector<GateToggle*> inputs;
    std::vector<GateReciever*> outputs;
private:
    bool m_bDeleteGates = true; //Delete gates on destructor
};

#endif // CIRCUIT_H

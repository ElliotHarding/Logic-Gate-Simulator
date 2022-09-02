#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <vector>
#include <QMap>
#include <QList>

class Gate;
class GateCollection;
class GateToggle;
class GateReciever;

//////////////////////////////////////////////////////////////////////////
///Circuit
class Circuit
{
public:
    Circuit(const QList<char>& inputLetters, const QList<char>& outputLetters);
    ~Circuit();

    GateCollection* createGateCollection();
    void deleteMainGates();

    std::vector<Gate*> mainGates;
    QMap<char, GateToggle*> inputs;
    QMap<char, GateReciever*> outputs;
private:
    bool m_bDeleteGates = true; //Delete gates on destructor
};

#endif // CIRCUIT_H

#ifndef SAVINGTEMPLATES_H
#define SAVINGTEMPLATES_H

#endif // SAVINGTEMPLATES_H

#include <string>
#include <QPoint>
#include <vector>
#include <fstream>

#include "gate.h"
#include "gateand.h"
#include "gatenot.h"
#include "gateor.h"
#include "GateToggle.h"
#include "GateReciever.h"
#include "gatefield.h"
#include "gatecollection.h"

#define nextLine gateStream >> line;

struct NodeAndIds {Node* pNode; int id; int linkedId;};

class GateReader
{
public:

    void readInGateFieldGates(std::ifstream& gateStream, GateField* gf);
    GateCollection* readGateCollection(std::ifstream& gateStream);

private:

    Gate* readGate(std::ifstream& gateStream, std::string& line);
    NodeIds readNode(std::ifstream& gateStream);

    void linkNodes(std::vector<Gate*> gates, std::vector<NodeAndIds> nodes);
};



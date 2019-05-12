#ifndef SAVINGTEMPLATES_H
#define SAVINGTEMPLATES_H

#endif // SAVINGTEMPLATES_H

#include <string>
#include <QPoint>
#include <vector>
#include <fstream>

#include "allgates.h"
#include "gatefield.h"

#define nextLine gateStream >> line;

struct NodeAndIds {Node* pNode; int id; int linkedId;};

class GateReader
{
public:

    void readInGateFieldGates(std::ifstream& gateStream, GateField* gf);
    GateCollection* readGateCollection(std::ifstream& gateStream);

private:

    std::vector<Gate*> readGates(std::ifstream& gateStream);
    Gate* readGate(std::ifstream& gateStream, std::string& line, std::vector<NodeIds>& linkInfo);
    NodeIds readNode(std::ifstream& gateStream);
    int tryStoi(std::string, int);
    void linkNodes(std::vector<Gate*>& gates, std::vector<NodeIds> linkInfo);
    bool SearchGatesForNode(std::vector<Gate*>& gates, id _id, Node*& n);
};



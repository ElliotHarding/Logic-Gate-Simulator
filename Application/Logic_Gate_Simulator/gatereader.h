#ifndef SAVINGTEMPLATES_H
#define SAVINGTEMPLATES_H

#include <string>
#include <QPoint>
#include <vector>
#include <QDomDocument>

class Gate;
class Node;
class GateCollection;
class GateField;
struct NodeIds;

class DLG_Home;

typedef int id;

class CustomGateReader
{
public:
    std::vector<QString> getCustomGateNames();
    GateCollection* spawnCustomGate(const QString& name);
    bool deleteCustomGate(const QString& name);
};

class GateReader
{
public:
    bool ReadGateField(const QString& fileName, GateField* pNewGateFeild, QString& errorMessage);
    bool ReadGateCollection(QDomDocument& doc, GateCollection*& gCollection);

    static void linkNodes(std::vector<Gate*>& gates, const std::vector<NodeIds>& linkInfo);

private:
    struct NodeAndIds {Node* pNode; int id; std::vector<int> linkedIds;};

    std::vector<Gate*> readGates(QDomDocument& doc);
    Gate* readGate(std::ifstream& gateStream, std::string& line, std::vector<NodeIds>& linkInfo);
    NodeIds readNode(std::ifstream& gateStream);
    int tryStoi(const std::string&, const int&);
    static bool SearchGatesForNode(std::vector<Gate*>& gates, const id& _id, Node*& n);
};

class Saver
{
public:
    bool saveGateField(GateField* pGateFeild, DLG_Home* pHome);
    bool saveGateCollection(GateCollection* pGateCollection, const QString& name, DLG_Home* pHome);
};

#endif // SAVINGTEMPLATES_H

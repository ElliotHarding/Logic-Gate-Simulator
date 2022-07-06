#ifndef SAVINGTEMPLATES_H
#define SAVINGTEMPLATES_H

#include <QString>
#include <vector>

class Gate;
class Node;
class GateCollection;
class GateField;
struct NodeIds;

class QFile;

class QDomElement;

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
    bool ReadGateCollection(const QString& filePath, GateCollection*& gCollection);

    static void linkNodes(std::vector<Gate*>& gates, const std::vector<NodeIds>& linkInfo);

private:
    struct NodeAndIds {Node* pNode; int id; std::vector<int> linkedIds;};

    std::vector<Gate*> readGates(QDomElement& gatesParent);
    Gate* readGate(QDomElement& gate, std::vector<NodeIds>& linkInfo);
    std::vector<NodeIds> readNodes(QDomElement& gate, std::vector<NodeIds>& linkInfo);
    void readNodeTypes(QDomElement& gate, std::vector<NodeIds>& linkInfo, std::vector<NodeIds>& nodeInfo, const QString& nodeType);
    int tryReadInt(const QString& value, const int& defaultVal);
    static bool SearchGatesForNode(std::vector<Gate*>& gates, const id& _id, Node*& n);
};

class Saver
{
public:
    bool saveGateField(GateField* pGateFeild, DLG_Home* pHome);
    bool saveGateCollection(GateCollection* pGateCollection, const QString& name, DLG_Home* pHome);
    bool saveScript(QString& currentSavePath, const QString& script, const uint& inputs, const uint& outputs, DLG_Home* pHome);
private:
    void saveScriptFile(QFile& file, const QString& script, const uint& inputs, const uint& outputs);
};

#endif // SAVINGTEMPLATES_H

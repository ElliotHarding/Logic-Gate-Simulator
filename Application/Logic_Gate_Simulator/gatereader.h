#ifndef SAVINGTEMPLATES_H
#define SAVINGTEMPLATES_H

#include <QString>
#include <vector>
#include "gatecollection.h"

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
    std::vector<Gate*> readGates(QDomElement& gatesParent);
    Gate* readGate(QDomElement& gate, std::vector<NodeIds>& linkInfo, std::vector<int>& gateLabelAttachIds, std::vector<std::pair<Gate*, int>>& gateAndTextLabelIdPairs, std::vector<TextLabel*>& labelGates);
    std::vector<NodeIds> readNodes(QDomElement& gate, std::vector<NodeIds>& linkInfo);
    std::vector<int> readAttachedLabelIds(QDomElement& gate);
    void attachLabels(std::vector<std::pair<Gate*, int>>& gateAndTextLabelIdPairs, std::vector<TextLabel*>& labelGates);
    void readNodeTypes(QDomElement& gate, std::vector<NodeIds>& linkInfo, std::vector<NodeIds>& nodeInfo, const QString& nodeType);
    int tryReadInt(const QString& value, const int& defaultVal);
    static bool searchGatesForNode(std::vector<Gate*>& gates, const id& _id, Node*& n);
};

class Saver
{
public:
    bool saveGateField(GateField* pGateFeild, DLG_Home* pHome);
    bool saveGateCollection(GateCollection* pGateCollection, const QString& name, DLG_Home* pHome);
};

#endif // SAVINGTEMPLATES_H

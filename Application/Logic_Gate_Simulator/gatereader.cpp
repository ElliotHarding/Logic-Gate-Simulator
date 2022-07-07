#include "gatereader.h"
#include "dlg_home.h"
#include "gatefield.h"
#include "allgates.h"

#include <QDebug>
#include <QDir>
#include <QDomDocument>

namespace Settings
{
const QString XMLElement = "xml";

const QString CustomGateFile = ".CustomGate";
const QString CustomGatesLocation = "CustomGates/";

const QString GateFeildFile = ".GateField";

const QString GateCollectionElement = "GateCollection";
}

bool GateReader::ReadGateField(const QString& fileName, GateField* pNewGateFeild, QString& errorMessage)
{   
    if(!pNewGateFeild)
    {
        errorMessage = "Internal Error - GateFeild pointer null";
        return false;
    }

    if(!fileName.contains(Settings::GateFeildFile))
    {
        errorMessage = "File not in gatefield format.";
        return false;
    }

    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        errorMessage = "Failed to open file";
        return false;
    }

    QDomDocument doc;
    doc.setContent(&file);

    QDomElement gateField = doc.firstChildElement(Settings::GateFieldElement);
    if(gateField.isNull())
    {
        errorMessage = "Failed reading file";
        file.close();
        return false;
    }

    const uint frequency = tryReadInt(gateField.attribute(Settings::GateFieldFrequencyTag), 200);
    pNewGateFeild->setUpdateFrequency(frequency);

    const std::vector<Gate*> gates = readGates(gateField);
    file.close();

    for (Gate* pGate : gates)
    {
        pGate->AssignNewNodeIds();
        pNewGateFeild->AddGate(pGate, false);
    }

    return true;
}

bool GateReader::ReadGateCollection(const QString& filePath, GateCollection*& gCollection)
{
    QFile gateCollectionFile(filePath);
    if(!gateCollectionFile.open(QIODevice::ReadOnly))
    {
        return false;
    }

    QDomDocument doc;
    doc.setContent(&gateCollectionFile);

    QDomElement gateCollection = doc.firstChildElement(Settings::GateCollectionElement);
    if(gateCollection.isNull())
    {
        gateCollectionFile.close();
        return false;
    }

    QDomElement gateCollectionGate = gateCollection.firstChildElement(Settings::GateElement);
    if(gateCollectionGate.isNull())
    {
        gateCollectionFile.close();
        return false;
    }

    const GateType type = (GateType)tryReadInt(gateCollectionGate.attribute(Settings::GateTypeTag), GATE_NULL);
    if(type != GateType::GATE_COLLECTION)
    {
        gateCollectionFile.close();
        return false;
    }

    gCollection = new GateCollection(readGates(gateCollectionGate));
    gCollection->AssignNewNodeIds();

    gateCollectionFile.close();

    return true;
}

std::vector<Gate*> GateReader::readGates(QDomElement& gatesParent)
{
    std::vector<Gate*> gates;
    std::vector<NodeIds> linkInfo;

    auto gateElement = gatesParent.firstChildElement(Settings::GateElement);
    while(!gateElement.isNull())
    {
        Gate* newReadGate = readGate(gateElement, linkInfo);
        if(newReadGate != nullptr)
        {
            gates.push_back(newReadGate);
        }
        gateElement = gateElement.nextSiblingElement(Settings::GateElement);
    }

    linkNodes(gates, linkInfo);

    return gates;
}

Gate* GateReader::readGate(QDomElement& gateElement, std::vector<NodeIds>& linkInfo)
{
    const GateType type = (GateType)tryReadInt(gateElement.attribute(Settings::GateTypeTag), GATE_NULL);
    const int posX = tryReadInt(gateElement.attribute(Settings::GatePosXTag), 0);
    const int posY = tryReadInt(gateElement.attribute(Settings::GatePosYTag), 0);

    std::vector<NodeIds> nodeInfo = readNodes(gateElement, linkInfo);

    switch(type)
    {
    case GateType::GATE_AND:
    {
        if(nodeInfo.size() == 3)
        {
            return new GateAnd(posX, posY, nodeInfo[0].id, nodeInfo[1].id, nodeInfo[2].id);
        }
        break;
    }

    case GateType::GATE_OR:
    {
        if(nodeInfo.size() == 3)
        {
            return new GateOr(posX, posY, nodeInfo[0].id, nodeInfo[1].id, nodeInfo[2].id);
        }
        break;
    }

    case GateType::GATE_COLLECTION:
    {
        std::vector<Gate*> subGates;

        auto subGateElement = gateElement.firstChildElement(Settings::GateElement);
        while(!subGateElement.isNull())
        {
            Gate* subGate = readGate(subGateElement, linkInfo);
            if(subGate != nullptr)
            {
                subGates.push_back(subGate);
            }
            subGateElement = subGateElement.nextSiblingElement(Settings::GateElement);
        }

        return new GateCollection(subGates);
    }

    case GateType::GATE_NOT:
    {
        if(nodeInfo.size() == 2)
        {
            return new GateNot(posX, posY, nodeInfo[0].id, nodeInfo[1].id);
        }
        break;
    }

    case GateType::GATE_EMMITTER:
    {
        if(nodeInfo.size() == 1)
        {
            return new GateToggle(posX, posY, nodeInfo[0].id, gateElement.attribute(Settings::GateTogglePowerStateTag) == "1");
        }
        break;
    }

    case GateType::GATE_RECIEVER:
    {
        if(nodeInfo.size() == 1)
        {
            return new GateReciever(posX, posY, nodeInfo[0].id);
        }
        break;
    }

    case GateType::GATE_CONST_ACTIVE:
    {
        if(nodeInfo.size() == 1)
        {
            return new GateConstantActive(posX, posY, nodeInfo[0].id);
        }
        break;
    }

    case GateType::GATE_CONST_INACTIVE:
    {
        if(nodeInfo.size() == 1)
        {
            return new GateConstantInactive(posX, posY, nodeInfo[0].id);
        }
        break;
    }

    case GateType::GATE_TIMER:
    {
        if(nodeInfo.size() == 1)
        {
            return new GateTimer(posX, posY, nodeInfo[0].id, tryReadInt(gateElement.attribute(Settings::GateTimerFrequencyTag), 500));
        }
        break;
    }

    case GateType::GATE_TRI_OR:
    {
        if(nodeInfo.size() == 4)
        {
            return new GateTriOr(posX, posY, nodeInfo[0].id, nodeInfo[1].id, nodeInfo[2].id, nodeInfo[3].id);
        }
        break;
    }

    case GateType::GATE_TRI_AND:
    {
        if(nodeInfo.size() == 4)
        {
            return new GateTriAnd(posX, posY, nodeInfo[0].id, nodeInfo[1].id, nodeInfo[2].id, nodeInfo[3].id);
        }
        break;
    }

    case GateType::GATE_TRI_EOR:
    {
        if(nodeInfo.size() == 4)
        {
            return new GateTriEor(posX, posY, nodeInfo[0].id, nodeInfo[1].id, nodeInfo[2].id, nodeInfo[3].id);
        }
        break;
    }

    case GateType::GATE_NUMBER_OUT:
    {
        if(nodeInfo.size() == 4)
        {
            return new GateNumberOutput(posX, posY, nodeInfo[0].id, nodeInfo[1].id, nodeInfo[2].id, nodeInfo[3].id);
        }
        break;
    }

    case GateType::GATE_EOR:
    {
        if(nodeInfo.size() == 3)
        {
            return new GateEor(posX, posY, nodeInfo[0].id, nodeInfo[1].id, nodeInfo[2].id);
        }
        break;
    }

    case GateType::GATE_TEXT_LABEL:
    {
        return new TextLabel(posX, posY, gateElement.attribute(Settings::GateTextLabelTextTag));
    }

    case GateType::GATE_FPGA:
    {
        QString script = gateElement.attribute(Settings::FPGAGateScriptElement);

        std::vector<NodeIds> inputNodeIds;
        std::vector<NodeIds> dummyLinkInfo;
        readNodeTypes(gateElement, dummyLinkInfo, inputNodeIds, Settings::NodeTypeInputElement);

        std::vector<NodeIds> outputNodeIds;
        readNodeTypes(gateElement, dummyLinkInfo, outputNodeIds, Settings::NodeTypeOutputElement);

        return new GateFPGA(script, inputNodeIds, outputNodeIds, posX, posY);
    }

    case GATE_NULL:
    default:
        qDebug() << "GateReader::readGate - Failed to read a gate! Gate type not found.";
        return nullptr;
    }

    qDebug() << "GateReader::readGate - node info read incorrectly";
    return nullptr;
}

std::vector<NodeIds> GateReader::readNodes(QDomElement& gate, std::vector<NodeIds>& linkInfo)
{
    std::vector<NodeIds> retNodeInfo;

    readNodeTypes(gate, linkInfo, retNodeInfo, Settings::NodeTypeInputElement);
    readNodeTypes(gate, linkInfo, retNodeInfo, Settings::NodeTypeOutputElement);

    return retNodeInfo;
}

void GateReader::readNodeTypes(QDomElement& gate, std::vector<NodeIds>& linkInfo, std::vector<NodeIds>& nodeInfo, const QString& nodeType)
{
    auto node = gate.firstChildElement(nodeType);
    while(!node.isNull())
    {
        NodeIds nodeIds;
        nodeIds.id = tryReadInt(node.attribute(Settings::NodeIdElement), -1);

        QDomElement linkedIds = node.firstChildElement(Settings::NodeLinkedIdsElement);
        if(!linkedIds.isNull())
        {
            auto linkedNode = linkedIds.firstChildElement(Settings::NodeLinkedIdElement);
            while(!linkedNode.isNull())
            {
                nodeIds.linkedIds.push_back(tryReadInt(linkedNode.attribute(Settings::NodeIdElement), -1));
                linkedNode = linkedNode.nextSiblingElement(Settings::NodeLinkedIdElement);
            }
        }

        nodeInfo.push_back(nodeIds);
        linkInfo.push_back(nodeIds);

        node = node.nextSiblingElement(nodeType);
    }
}

int GateReader::tryReadInt(const QString& value, const int& defaultVal)
{
    bool ok = false;
    int retVal = value.toInt(&ok);

    if(ok)
    {
        return retVal;
    }
    return defaultVal;
}

void GateReader::linkNodes(std::vector<Gate*>& gates, const std::vector<NodeIds>& linkInfo)
{
    for (const NodeIds& link : linkInfo)
    {
        if(link.id != -1)
        {
            Node* node1;
            if(SearchGatesForNode(gates, link.id, node1))
            {
                for (const id& otherId : link.linkedIds)
                {
                    if(otherId != -1)
                    {
                        Node* node2;
                        if(SearchGatesForNode(gates, otherId, node2))
                        {
                            (node2)->LinkNode(node1);
                            (node1)->LinkNode(node2);
                        }
                        else
                        {
                            qDebug() << "GateReader::linkNodes - Failed to find node! " << otherId;
                        }
                    }
                }
            }
            else
            {
                qDebug() << "GateReader::linkNodes - Failed to find node! " << link.id;
            }
        }
    }
}

bool GateReader::SearchGatesForNode(std::vector<Gate*>& gates, const id& _id, Node*& n)
{
    for (Gate* gate : gates)
    {
        if(gate->FindNodeWithId(_id, n))
            return true;
    }
    return false;
}

bool Saver::saveGateField(GateField* pGateFeild, DLG_Home* pHome)
{
    QString dir = QFileDialog::getExistingDirectory(pHome, "Open Directory",
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    QFile file(dir + "/" + pGateFeild->name() + Settings::GateFeildFile);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return false;
    }

    QDomDocument saveDoc(Settings::XMLElement);
    pGateFeild->SaveData(saveDoc);

    QTextStream stream(&file);
    stream << saveDoc.toString();

    file.close();

    return true;
}

bool Saver::saveGateCollection(GateCollection* pGateCollection, const QString& name, DLG_Home* pHome)
{
    if(!QDir(Settings::CustomGatesLocation).exists())
        QDir().mkdir(Settings::CustomGatesLocation);

    QFile file(Settings::CustomGatesLocation + name + Settings::CustomGateFile);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return false;
    }

    QDomDocument saveDoc(Settings::XMLElement);
    QDomElement saveDocElement = saveDoc.createElement(Settings::GateCollectionElement);
    pGateCollection->SaveData(saveDoc, saveDocElement);
    saveDoc.appendChild(saveDocElement);

    QTextStream stream(&file);
    stream << saveDoc.toString();

    file.close();

    pHome->UpdateCustomGateListWidget();

    return true;
}

std::vector<QString> CustomGateReader::getCustomGateNames()
{
    QStringList nameFilter("*" + Settings::CustomGateFile);
    QDir directory(Settings::CustomGatesLocation);
    QStringList fileList = directory.entryList(nameFilter);

    std::vector<QString> names;
    for (const QString& file : fileList)
    {
        names.push_back(file.left(file.length() - 11));
    }

    return names;
}

GateCollection* CustomGateReader::spawnCustomGate(const QString &name)
{
    const QString customGateFile(Settings::CustomGatesLocation + name + Settings::CustomGateFile);

    GateCollection* cg;
    static GateReader gReader;
    if(gReader.ReadGateCollection(customGateFile, cg))
    {
        return cg;
    }

    return nullptr;
}

bool CustomGateReader::deleteCustomGate(const QString &name)
{
    const QString fileName = Settings::CustomGatesLocation + name + Settings::CustomGateFile;
    QFile file(fileName);
    if(file.remove())
    {
        return true;
    }
    return false;
}

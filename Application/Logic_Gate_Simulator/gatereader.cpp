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

const QString GateFieldElement = "GateField";
const QString GateCollectionElement = "GateCollection";

const QString GateElement = "Gate";

const QString NodeTypeInputElement = "InputNode";
const QString NodeTypeOutputElement = "OutputNode";
const QString NodeLinkedIdsElement = "LinkedIds";
const QString NodeIdElement = "id";

const QString FPGAGateScriptElement = "Script";
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
    if(!file.open(QIODevice::ReadOnly))
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

    const std::vector<Gate*> gates = readGates(gateField);
    file.close();

    for (Gate* pGate : gates)
    {
        pGate->AssignNewNodeIds();
        pNewGateFeild->AddGate(pGate, false);
    }

    return true;
}

bool GateReader::ReadGateCollection(QDomDocument& doc, GateCollection*& gCollection)
{
    QDomElement gateCollection = doc.firstChildElement(Settings::GateCollectionElement);
    if(gateCollection.isNull())
    {
        return false;
    }

    gCollection = new GateCollection(readGates(gateCollection));
    gCollection->AssignNewNodeIds();

    return true;
}

std::vector<Gate*> GateReader::readGates(QDomElement& gatesParent)
{
    std::vector<Gate*> gates;
    std::vector<NodeIds> linkInfo;

    QDomNodeList gateNodes = gatesParent.elementsByTagName(Settings::GateElement);
    for(int i = 0; i < gateNodes.size(); i++)
    {
        if(gateNodes.at(i).isElement())
        {
            QDomElement gateElement = gateNodes.at(i).toElement();
            Gate* newReadGate = readGate(gateElement, linkInfo);
            if(newReadGate != nullptr)
            {
                gates.push_back(newReadGate);
            }
        }
    }

    linkNodes(gates, linkInfo);

    return gates;
}

Gate* GateReader::readGate(QDomElement& gateElement, std::vector<NodeIds>& linkInfo)
{
    const GateType type = (GateType)tryReadInt(gateElement.attribute("type"), GATE_NULL);
    const int posX = tryReadInt(gateElement.attribute("posX"), 0);
    const int posY = tryReadInt(gateElement.attribute("posY"), 0);

    std::vector<NodeIds> nodeInfo = readNodes(gateElement, linkInfo);

    //Gate that will be instanciated
    Gate* rGate = nullptr;

    switch(type)
    {
    case GateType::GATE_AND:
    {
        if(nodeInfo.size() == 3)
        {
            rGate = new GateAnd(posX, posY, nodeInfo[0].id, nodeInfo[1].id, nodeInfo[2].id);
        }
        else
        {
            qDebug() << "GateReader::readGate - node info read incorrectly";
        }
        break;
    }

    case GateType::GATE_OR:
    {
        if(nodeInfo.size() == 3)
        {
            rGate = new GateOr(posX, posY, nodeInfo[0].id, nodeInfo[1].id, nodeInfo[2].id);
        }
        else
        {
            qDebug() << "GateReader::readGate - node info read incorrectly";
        }
        break;
    }

    case GateType::GATE_COLLECTION:
    {
        std::vector<Gate*> rGates;

        QDomNodeList gateNodes = gateElement.elementsByTagName(Settings::GateElement);
        for(int i = 0; i < gateNodes.size(); i++)
        {
            if(gateNodes.at(i).isElement())
            {
                QDomElement gateElement = gateNodes.at(i).toElement();
                Gate* subGate = readGate(gateElement, linkInfo);
                if(subGate != nullptr)
                {
                    rGates.push_back(subGate);
                }
            }
        }

        rGate = new GateCollection(rGates);
        return rGate;
        break;
    }

    case GateType::GATE_NOT:
    {
        if(nodeInfo.size() == 2)
        {
            rGate = new GateNot(posX, posY, nodeInfo[0].id, nodeInfo[1].id);
        }
        else
        {
            qDebug() << "GateReader::readGate - node info read incorrectly";
        }
        break;
    }

    case GateType::GATE_EMMITTER:
    {
        if(nodeInfo.size() == 1)
        {
            rGate = new GateToggle(posX, posY, nodeInfo[0].id);
        }
        else
        {
            qDebug() << "GateReader::readGate - node info read incorrectly";
        }
        break;
    }

    case GateType::GATE_RECIEVER:
    {
        if(nodeInfo.size() == 1)
        {
            rGate = new GateReciever(posX, posY, nodeInfo[0].id);
        }
        else
        {
            qDebug() << "GateReader::readGate - node info read incorrectly";
        }
        break;
    }

    case GateType::GATE_CONST_ACTIVE:
    {
        if(nodeInfo.size() == 1)
        {
            rGate = new GateConstantActive(posX, posY, nodeInfo[0].id);
        }
        else
        {
            qDebug() << "GateReader::readGate - node info read incorrectly";
        }
        break;
    }

    case GateType::GATE_CONST_INACTIVE:
    {
        if(nodeInfo.size() == 1)
        {
            rGate = new GateConstantInactive(posX, posY, nodeInfo[0].id);
        }
        else
        {
            qDebug() << "GateReader::readGate - node info read incorrectly";
        }
        break;
    }

    case GateType::GATE_TIMER:
    {
        if(nodeInfo.size() == 1)
        {
            rGate = new GateTimer(posX, posY, nodeInfo[0].id);
            dynamic_cast<GateTimer*>(rGate)->setFrequency(tryReadInt(gateElement.attribute("Frequency"), 500));
        }
        else
        {
            qDebug() << "GateReader::readGate - node info read incorrectly";
        }
        break;
    }

    case GateType::GATE_TRI_OR:
    {
        if(nodeInfo.size() == 4)
        {
            rGate = new GateTriOr(posX, posY, nodeInfo[0].id, nodeInfo[1].id, nodeInfo[2].id, nodeInfo[3].id);
        }
        else
        {
            qDebug() << "GateReader::readGate - node info read incorrectly";
        }
        break;
    }

    case GateType::GATE_TRI_AND:
    {
        if(nodeInfo.size() == 4)
        {
            rGate = new GateTriAnd(posX, posY, nodeInfo[0].id, nodeInfo[1].id, nodeInfo[2].id, nodeInfo[3].id);
        }
        else
        {
            qDebug() << "GateReader::readGate - node info read incorrectly";
        }
    }

    case GateType::GATE_TRI_EOR:
    {
        if(nodeInfo.size() == 4)
        {
            rGate = new GateTriEor(posX, posY, nodeInfo[0].id, nodeInfo[1].id, nodeInfo[2].id, nodeInfo[3].id);
        }
        else
        {
            qDebug() << "GateReader::readGate - node info read incorrectly";
        }
        break;
    }

    case GateType::GATE_NUMBER_OUT:
    {
        if(nodeInfo.size() == 4)
        {
            rGate = new GateNumberOutput(posX, posY, nodeInfo[0].id, nodeInfo[1].id, nodeInfo[2].id, nodeInfo[3].id);
        }
        else
        {
            qDebug() << "GateReader::readGate - node info read incorrectly";
        }
        break;
    }

    case GateType::GATE_EOR:
    {
        if(nodeInfo.size() == 3)
        {
            rGate = new GateEor(posX, posY, nodeInfo[0].id, nodeInfo[1].id, nodeInfo[2].id);
        }
        else
        {
            qDebug() << "GateReader::readGate - node info read incorrectly";
        }
        break;
    }

    case GateType::GATE_FPGA:
    {
        QString script = gateElement.attribute(Settings::FPGAGateScriptElement);

        std::vector<NodeIds> inputNodeIds;
        std::vector<NodeIds> dummyLinkInfo;
        readNodeTypes(gateElement, dummyLinkInfo, inputNodeIds, Settings::NodeTypeInputElement);

        std::vector<NodeIds> outputNodeIds;
        readNodeTypes(gateElement, dummyLinkInfo, outputNodeIds, Settings::NodeTypeOutputElement);

        rGate = new GateFPGA(script, inputNodeIds, outputNodeIds, posX, posY);
        break;
    }

    case GATE_NULL:
    default:
        qDebug() << "GateReader::readGate - Failed to read a gate! Gate type not found.";
        return nullptr;
    }

    return rGate;
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
    QDomNodeList nodeNodes = gate.elementsByTagName(nodeType);
    for(int i = 0; i < nodeNodes.size(); i++)
    {
        if(nodeNodes.at(i).isElement())
        {
            QDomElement nodeElement = nodeNodes.at(i).toElement();

            NodeIds nodeIds;
            nodeIds.id = tryReadInt(nodeElement.attribute(Settings::NodeIdElement), -1);

            QDomElement linkedIds = nodeElement.firstChildElement(Settings::NodeLinkedIdsElement);
            QDomNodeList linkNodes = linkedIds.childNodes();
            for(int i = 0; i < linkNodes.size(); i++)
            {
                if(linkNodes.at(i).isElement())
                {
                    nodeIds.linkedIds.push_back(tryReadInt(linkNodes.at(i).toElement().tagName(), -1));
                }
            }

            nodeInfo.push_back(nodeIds);
            linkInfo.push_back(nodeIds);
        }
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
    QDomElement gateFieldElement = saveDoc.createElement(Settings::GateFieldElement);
    pGateFeild->SaveData(saveDoc, gateFieldElement);
    saveDoc.appendChild(gateFieldElement);

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
    QFile customGateFile(Settings::CustomGatesLocation + name + Settings::CustomGateFile);

    if(!customGateFile.open(QIODevice::ReadOnly))
    {
        return nullptr;
    }

    QDomDocument doc;
    doc.setContent(&customGateFile);

    GateCollection* cg;
    static GateReader gReader;
    if(gReader.ReadGateCollection(doc, cg))
    {
        customGateFile.close();
        return cg;
    }

    customGateFile.close();

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

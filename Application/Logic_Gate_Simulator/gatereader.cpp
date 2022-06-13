#include "gatereader.h"
#include "dlg_home.h"

#include <QDebug>
#include <QDir>

namespace Settings
{
const QString CustomGateFile = ".CustomGate";
const QString CustomGatesLocation = "CustomGates/";

const QString GateFeildFile = ".GateField";
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

    std::ifstream saveFile(fileName.toUtf8());
    if(!saveFile.is_open())
    {
        errorMessage = "Failed to open file";
        return false;
    }

    const std::vector<Gate*> gates = readGates(saveFile);
    saveFile.close();

    for (Gate* pGate : gates)
    {
        pGate->AssignNewNodeIds();
        pNewGateFeild->AddGate(pGate);
    }

    return true;
}

bool GateReader::ReadGateCollection(std::ifstream& gateStream, GateCollection*& gCollection)
{
    std::string line;
    nextLine //<GATE> tag
    nextLine //Type number 7

    //Enabled
    gateStream >> line;
    bool enabled = false;
    tryStoi(line, enabled);

    nextLine //Empty element meant for xPos of a noraml gate, might add info here
    nextLine //Empty element meant for yPos of a normal gate, might add info here

    gCollection = new GateCollection(readGates(gateStream));
    gCollection->AssignNewNodeIds();

    return true;
}

std::vector<Gate *> GateReader::readGates(std::ifstream &gateStream)
{
    std::string line;
    std::vector<Gate*> gates;
    std::vector<NodeIds> linkInfo;

    nextLine
    while(line == SAVE_TAG_GATE)
    {
        gates.push_back(readGate(gateStream, line, linkInfo));
        nextLine
    }

    linkNodes(gates, linkInfo);

    return gates;
}

Gate* GateReader::readGate(std::ifstream& gateStream, std::string& line, std::vector<NodeIds>& linkInfo)
{
    //Get gate header info
    std::string type, enabled, posX, posY;
    gateStream >> type >> enabled >> posX >> posY;

    //Gate that will be instanciated
    Gate* rGate;

    switch(tryStoi(type, GATE_NULL))
    {

    case GateType::GATE_AND:
    {
        NodeIds n1 = readNode(gateStream);
        NodeIds n2 = readNode(gateStream);
        NodeIds n3 = readNode(gateStream);

        rGate = new GateAnd(stoi(posX), stoi(posY), n1.id, n2.id, n3.id);

        linkInfo.push_back(n1);
        linkInfo.push_back(n2);
        linkInfo.push_back(n3);

        break;
    }

    case GateType::GATE_OR:
    {
        NodeIds n1 = readNode(gateStream);
        NodeIds n2 = readNode(gateStream);
        NodeIds n3 = readNode(gateStream);

        rGate = new GateOr(stoi(posX), stoi(posY), n1.id, n2.id, n3.id);

        linkInfo.push_back(n1);
        linkInfo.push_back(n2);
        linkInfo.push_back(n3);

        break;
    }

    case GateType::GATE_COLLECTION:
    {
        std::vector<Gate*> rGates;

        nextLine
        while (line == SAVE_TAG_GATE)
        {
            rGates.push_back(readGate(gateStream, line, linkInfo));
            nextLine
        }
        rGate = new GateCollection(rGates);
        break;
    }

    case GateType::GATE_NOT:
    {
        NodeIds n1 = readNode(gateStream);
        NodeIds n2 = readNode(gateStream);

        rGate = new GateNot(stoi(posX), stoi(posY), n1.id, n2.id);

        linkInfo.push_back(n1);
        linkInfo.push_back(n2);
        break;
    }

    case GateType::GATE_EMMITTER:
    {
        NodeIds n1 = readNode(gateStream);

        rGate = new GateToggle(stoi(posX), stoi(posY), n1.id);

        linkInfo.push_back(n1);
        break;
    }

    case GateType::GATE_RECIEVER:
    {
        NodeIds n1 = readNode(gateStream);

        rGate = new GateReciever(stoi(posX), stoi(posY), n1.id);

        linkInfo.push_back(n1);
        break;
    }

    case GateType::GATE_CONST_ACTIVE:
    {
        NodeIds n1 = readNode(gateStream);

        rGate = new GateConstantActive(stoi(posX), stoi(posY), n1.id);

        linkInfo.push_back(n1);
        break;
    }

    case GateType::GATE_CONST_INACTIVE:
    {
        NodeIds n1 = readNode(gateStream);

        rGate = new GateConstantInactive(stoi(posX), stoi(posY), n1.id);

        linkInfo.push_back(n1);
        break;
    }

    case GateType::GATE_TIMER:
    {
        NodeIds n1 = readNode(gateStream);

        std::string frequency;
        gateStream >> frequency;

        rGate = new GateTimer(stoi(posX), stoi(posY), n1.id);
        dynamic_cast<GateTimer*>(rGate)->setFrequency(tryStoi(frequency, 500));

        linkInfo.push_back(n1);
        break;
    }

    case GateType::GATE_TRI_OR:
    {
        NodeIds n1 = readNode(gateStream);
        NodeIds n2 = readNode(gateStream);
        NodeIds n3 = readNode(gateStream);
        NodeIds n4 = readNode(gateStream);

        rGate = new GateTriOr(stoi(posX), stoi(posY), n1.id, n2.id, n3.id, n4.id);

        linkInfo.push_back(n1);
        linkInfo.push_back(n2);
        linkInfo.push_back(n3);
        linkInfo.push_back(n4);
        break;
    }

    case GateType::GATE_TRI_AND:
    {
        NodeIds n1 = readNode(gateStream);
        NodeIds n2 = readNode(gateStream);
        NodeIds n3 = readNode(gateStream);
        NodeIds n4 = readNode(gateStream);

        rGate = new GateTriAnd(stoi(posX), stoi(posY), n1.id, n2.id, n3.id, n4.id);

        linkInfo.push_back(n1);
        linkInfo.push_back(n2);
        linkInfo.push_back(n3);
        linkInfo.push_back(n4);
        break;
    }

    case GateType::GATE_TRI_EOR:
    {
        NodeIds n1 = readNode(gateStream);
        NodeIds n2 = readNode(gateStream);
        NodeIds n3 = readNode(gateStream);
        NodeIds n4 = readNode(gateStream);

        rGate = new GateTriEor(stoi(posX), stoi(posY), n1.id, n2.id, n3.id, n4.id);

        linkInfo.push_back(n1);
        linkInfo.push_back(n2);
        linkInfo.push_back(n3);
        linkInfo.push_back(n4);
        break;
    }

    case GateType::GATE_NUMBER_OUT:
    {
        NodeIds n1 = readNode(gateStream);
        NodeIds n2 = readNode(gateStream);
        NodeIds n3 = readNode(gateStream);
        NodeIds n4 = readNode(gateStream);

        rGate = new GateNumberOutput(stoi(posX), stoi(posY), n1.id, n2.id, n3.id, n4.id);

        linkInfo.push_back(n1);
        linkInfo.push_back(n2);
        linkInfo.push_back(n3);
        linkInfo.push_back(n4);
        break;
    }

    case GateType::GATE_EOR:
    {
        NodeIds n1 = readNode(gateStream);
        NodeIds n2 = readNode(gateStream);
        NodeIds n3 = readNode(gateStream);

        rGate = new GateEor(stoi(posX), stoi(posY), n1.id, n2.id, n3.id);

        linkInfo.push_back(n1);
        linkInfo.push_back(n2);
        linkInfo.push_back(n3);

        break;
    }

    case GATE_NULL:
    default:
        qDebug() << "GateReader::readGate - Failed to read a gate!";
        return nullptr;
    }

    //Only valid gate types after this:

    //Enabled
    //Enabled no longer used

    //Read off </GATE> tag, but it's already been read for GateCollections
    if(rGate->GetType() != GateType::GATE_COLLECTION)
    {
        nextLine;
    }

    return rGate;
}

NodeIds GateReader::readNode(std::ifstream& gateStream)
{
    //read in strings
    std::string startTag, sID, linkedNodes, endTag;
    gateStream >> startTag >> sID >> linkedNodes >> endTag;

    //Apply string to nodeInfo
    NodeIds nodeInfo;
    nodeInfo.id = tryStoi(sID, -1);

    //Read linkedNodes string, into linkedIds vector
    std::vector<int> linkedIds;
    std::string stringBuild = "";
    for (size_t index = 0; index < linkedNodes.length(); index++)
    {
        //If at ',' or end of string
        if(linkedNodes[index] == ',' || index == linkedNodes.length() - 1)
        {
            nodeInfo.linkedIds.push_back(tryStoi(stringBuild, -1));
            stringBuild = "";
        }
        else
        {
            stringBuild += linkedNodes[index];
        }
    }
    return nodeInfo;
}

int GateReader::tryStoi(const std::string& s, const int& defaultVal)
{
    try
    {
        return std::stoi(s);
    }
    catch (...)
    {
        return defaultVal;
    }
}

void GateReader::linkNodes(std::vector<Gate*>& gates, const std::vector<NodeIds>& linkInfo)
{
    for (const NodeIds link : linkInfo)
    {
        if(link.id != -1)
        {
            Node* node1;
            if(SearchGatesForNode(gates, link.id, node1))
            {
                for (const id id_ : link.linkedIds)
                {
                    if(id_ != -1)
                    {
                        Node* node2;
                        if(SearchGatesForNode(gates, id_, node2))
                        {
                            (node2)->LinkNode(node1);
                            (node1)->LinkNode(node2);
                        }
                        else
                        {
                            qDebug() << "GateReader::linkNodes - Failed to find node! " << link.id;
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

    std::ofstream saveFile(dir.toStdString() + "/" + pGateFeild->name() + Settings::GateFeildFile.toStdString());

    if(saveFile.is_open())
    {
        pGateFeild->SaveData(saveFile);
        saveFile.close();
        return true;
    }

    return false;
}

bool Saver::saveGateCollection(GateCollection* pGateCollection, const std::string name, DLG_Home* pHome)
{
    if(!QDir(Settings::CustomGatesLocation).exists())
        QDir().mkdir(Settings::CustomGatesLocation);

    std::ofstream gateCollectionStream(Settings::CustomGatesLocation.toStdString() + name + Settings::CustomGateFile.toStdString());
    if(gateCollectionStream.is_open())
    {
        pGateCollection->SaveData(gateCollectionStream);
        gateCollectionStream.close();

        pHome->UpdateCustomGateListWidget();
        return true;
    }

    return false;
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
    std::ifstream customGateStream(Settings::CustomGatesLocation.toStdString() + name.toStdString());

    //Read into pointer and send to m_pParent
    if(customGateStream.is_open())
    {
        GateCollection* cg;
        static GateReader gReader;
        if(gReader.ReadGateCollection(customGateStream, cg))
        {
            customGateStream.close();
            return cg;
        }
        customGateStream.close();
    }

    return nullptr;
}

bool CustomGateReader::deleteCustomGate(const QString &name)
{
    std::string fileName = Settings::CustomGatesLocation.toStdString() + name.toStdString();
    if(std::remove(fileName.c_str()) == 0)
    {
        return true;
    }
    return false;
}

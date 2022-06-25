#include "gatereader.h"
#include "dlg_home.h"
#include "gatefield.h"
#include "allgates.h"

#include <QDebug>
#include <QDir>
#include <QDomDocument>

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

    QFile file;
    if(!file.open(QIODevice::ReadOnly))
    {
        errorMessage = "Failed to open file";
        return false;
    }

    QDomDocument doc;
    doc.setContent(&file);

    const std::vector<Gate*> gates = readGates(doc);
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
    gCollection = new GateCollection(readGates(doc));
    gCollection->AssignNewNodeIds();

    return true;
}

std::vector<Gate*> GateReader::readGates(QDomDocument& doc)
{
    std::vector<Gate*> gates;
    std::vector<NodeIds> linkInfo;

    linkNodes(gates, linkInfo);

    return gates;
}

Gate* GateReader::readGate(std::ifstream& gateStream, std::string& line, std::vector<NodeIds>& linkInfo)
{
    //Get gate header info
    std::string type, enabled, posX, posY;
    //gateStream >> type >> enabled >> posX >> posY;

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

        //~todo

        rGate = new GateCollection(rGates);
        return rGate;
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
        std::string frequency;
        //gateStream >> frequency;
        //~todo

        NodeIds n1 = readNode(gateStream);

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

    case GateType::GATE_FPGA:
    {
        std::string script;
        //std::getline(gateStream, line);//don't ask me why this is nessesary. It will be removed in future anyways.

        /* ~todo
        gateStream >> line;//"<Script>"
        while(true)
        {
            std::getline(gateStream, line);
            if(line == "</Script>")
            {
                break;
            }
            script += line + "\n";
        }

        std::vector<NodeIds> inputNodeIds;
        gateStream >> line; //<InputNodes>
        while(true)
        {
            gateStream >> line; //Either <Node> or </InputNodes>
            if(line == "</InputNodes>")
            {
                break;
            }

            //read in strings
            std::string sID, linkedNodes, endTag;
            gateStream >> sID >> linkedNodes >> endTag;

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

            inputNodeIds.push_back(nodeInfo);
            linkInfo.push_back(nodeInfo);
        }

        std::vector<NodeIds> outputNodeIds;
        gateStream >> line; //<OutputNodes>
        while(true)
        {
            gateStream >> line; //Either <Node> or </OutputNodes>
            if(line == "</OutputNodes>")
            {
                break;
            }

            //read in strings
            std::string sID, linkedNodes, endTag;
            gateStream >> sID >> linkedNodes >> endTag;

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

            outputNodeIds.push_back(nodeInfo);
            linkInfo.push_back(nodeInfo);
        }*/

        //rGate = new GateFPGA(QString::fromStdString(script), inputNodeIds, outputNodeIds, stoi(posX), stoi(posY));
        break;
    }

    case GATE_NULL:
    default:
        qDebug() << "GateReader::readGate - Failed to read a gate!";
        return nullptr;
    }

    return rGate;
}

NodeIds GateReader::readNode(std::ifstream& gateStream)
{
    //read in strings
    std::string startTag, sID, linkedNodes, endTag;
    //gateStream >> startTag >> sID >> linkedNodes >> endTag; ~todo

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

    QDomDocument saveDoc(dir + "/" + pGateFeild->name() + Settings::GateFeildFile);
    QDomElement gateFieldElement = saveDoc.createElement("GateField");
    pGateFeild->SaveData(saveDoc);
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

    QDomDocument saveDoc(Settings::CustomGatesLocation + name + Settings::CustomGateFile);
    QDomElement saveFileElement = saveDoc.createElement("GateCollectionSaveFile");
    pGateCollection->SaveData(saveDoc, saveFileElement);
    saveDoc.appendChild(saveFileElement);

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
    std::string fileName = Settings::CustomGatesLocation.toStdString() + name.toStdString();
    if(std::remove(fileName.c_str()) == 0)
    {
        return true;
    }
    return false;
}

#include "gatereader.h"

bool GateReader::ReadGateField(std::ifstream& gateStream, GateField* gf)
{
    if(!gf)
        return false;

    std::vector<Gate*> gates = readGates(gateStream);

    //Add loaded gates into gf
    for (Gate* gate : gates)
    {
        gate->AssignNewNodeIds();
        gf->AddGate(gate);
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
    gCollection->Enabled = enabled;
    gCollection->AssignNewNodeIds();

    /*
        So what I could do is read all the gateCollections into GateCollection objects
        & then whenever a gate collection is requested, just clone the objects
        and pass them to the requester

        Clone function's already implemented....
     */

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

        rGate = new GateAnd(n1.id, n2.id, n3.id);

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

        rGate = new GateOr(n1.id, n2.id, n3.id);

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

        rGate = new GateNot(n1.id, n2.id);

        linkInfo.push_back(n1);
        linkInfo.push_back(n2);
        break;
    }

    case GateType::GATE_EMMITTER:
    {
        NodeIds n1 = readNode(gateStream);

        rGate = new GateToggle(n1.id);

        linkInfo.push_back(n1);
        break;
    }

    case GateType::GATE_RECIEVER:
    {
        NodeIds n1 = readNode(gateStream);

        rGate = new GateReciever(n1.id);

        linkInfo.push_back(n1);
        break;
    }

    case GateType::GATE_CONST_ACTIVE:
    {
        NodeIds n1 = readNode(gateStream);

        rGate = new GateConstantActive(n1.id);

        linkInfo.push_back(n1);
        break;
    }

    case GateType::GATE_CONST_INACTIVE:
    {
        NodeIds n1 = readNode(gateStream);

        rGate = new GateConstantInactive(n1.id);

        linkInfo.push_back(n1);
        break;
    }

    case GateType::GATE_TIMER:
    {
        NodeIds n1 = readNode(gateStream);

        std::string frequency;
        gateStream >> frequency;

        rGate = new GateTimer(n1.id);
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

        rGate = new GateTriOr(n1.id, n2.id, n3.id, n4.id);

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

        rGate = new GateTriAnd(n1.id, n2.id, n3.id, n4.id);

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

        rGate = new GateTriEor(n1.id, n2.id, n3.id, n4.id);

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

        rGate = new GateNumberOutput(n1.id, n2.id, n3.id, n4.id);

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

        rGate = new GateEor(n1.id, n2.id, n3.id);

        linkInfo.push_back(n1);
        linkInfo.push_back(n2);
        linkInfo.push_back(n3);

        break;
    }

    case GATE_NULL:
    default:
        return nullptr;
    }

    //Only valid gate types after this:

    //Enabled
    bool isEnabled = false;
    tryStoi(enabled, isEnabled);
    rGate->Enabled = isEnabled;

    //Position
    rGate->SetPosition(stoi(posX),stoi(posY));

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

int GateReader::tryStoi(std::string s, int defaultVal)
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

void GateReader::linkNodes(std::vector<Gate *>& gates, std::vector<NodeIds> linkInfo)
{
    for (NodeIds link : linkInfo)
    {
        if(link.id != -1)
        {
            for (id id_ : link.linkedIds)
            {
                if(id_ != -1)
                {
                    Node* node1;
                    if(SearchGatesForNode(gates, link.id, node1))
                    {
                        Node* node2;
                        if(SearchGatesForNode(gates, id_, node2))
                        {
                            (node2)->LinkNode(node1);
                            (node1)->LinkNode(node2);
                        }
                        node2 = nullptr;
                    }
                    node1 = nullptr;
                }
            }
        }
    }
}

bool GateReader::SearchGatesForNode(std::vector<Gate*>& gates, id _id, Node*& n)
{
    for (Gate* gate : gates)
    {
        if(gate->FindNodeWithId(_id, n))
            return true;
    }
    return false;
}

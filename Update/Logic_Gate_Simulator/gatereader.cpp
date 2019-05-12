#include "gatereader.h"

void GateReader::readInGateFieldGates(std::ifstream& gateStream, GateField* gf)
{
    if(!gf)
        return;

    std::vector<Gate*> gates = readGates(gateStream);

    //Add loaded gates into gf
    for (Gate* gate : gates)
    {
        gf->addGameObject(gate);
    }
}

GateCollection* GateReader::readGateCollection(std::ifstream& gateStream)
{
    std::string line;
    nextLine //<GATE> tag
    nextLine //Type number 7
    return new GateCollection(readGates(gateStream));
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
    std::string type, posX, posY;
    gateStream >> type >> posX >> posY;

    //Generate correct gate tye
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

        rGate = new GateTimer(n1.id);

        linkInfo.push_back(n1);
        break;
    }

    case GATE_NULL:
        return nullptr;

    default:
        return nullptr;
    }

    rGate->SetPosition(stoi(posX),stoi(posY));

    nextLine;
    return rGate;
}

NodeIds GateReader::readNode(std::ifstream& gateStream)
{
    //read in strings
    std::string startTag, sID, slID, endTag;
    gateStream >> startTag >> sID >> slID >> endTag;

    //Apply string to nodeInfo
    NodeIds nodeInfo;
    nodeInfo.id = tryStoi(sID, -1);
    nodeInfo.linkedId = tryStoi(slID, -1);

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
        //todo
    }
}

void GateReader::linkNodes(std::vector<Gate *>& gates, std::vector<NodeIds> linkInfo)
{
    for (NodeIds link : linkInfo)
    {
        if(link.id != -1 && link.linkedId != -1)
        {
            Node* node1;
            if(SearchGatesForNode(gates, link.id, node1))
            {
                Node* node2;
                if(SearchGatesForNode(gates, link.id, node2))
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

bool GateReader::SearchGatesForNode(std::vector<Gate*>& gates, id _id, Node*& n)
{
    for (Gate* gate : gates)
    {
        if(gate->FindNodeWithId(_id, n))
            return true;
    }
    return false;
}

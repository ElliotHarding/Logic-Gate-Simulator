#include "gatereader.h"

void GateReader::readInGateFieldGates(std::ifstream& gateStream, GateField* gf)
{
    if(!gf)
        return;

    std::string line;
    std::vector<Gate*> gates;
    nextLine
    while(line == SAVE_TAG_GATE)
    {
        gates.push_back(readGate(gateStream, line));
        nextLine
    }

    //Add loaded gates into gf
    for (Gate* gate : gates)
    {
        gf->addGameObject(gate);
    }
}

GateCollection* GateReader::readGateCollection(std::ifstream& gateStream)
{
    std::vector<Gate*> rGates;
    std::string line;

    //Get all gates inside gate collection tags
    nextLine
    while (line == SAVE_TAG_GATE)
    {
        rGates.push_back(readGate(gateStream, line));
        nextLine
    }

    return new GateCollection(rGates);
}

Gate* GateReader::readGate(std::ifstream& gateStream, std::string& line)
{
    //Get gate header info
    std::string type, posX, posY;
    gateStream >> type >> posX >> posY;

    std::vector<NodeAndIds> allNodes;

    //Generate correct gate tye
    Gate* rGate;
    switch((GateType)std::stoi(type))
    {
    case GateType::GATE_AND:
        rGate = new GateAnd();
        break;
    case GateType::GATE_OR:
        rGate = new GateOr();
        break;
    case GateType::GATE_COLLECTION:
    {
        std::vector<Gate*> rGates;
        nextLine
        while (line == SAVE_TAG_GATE)
        {
            rGates.push_back(readGate(gateStream, line));
            nextLine
        }
        rGate = new GateCollection(rGates);

        rGate->SetPosition(stoi(posX),stoi(posY));

        return rGate;
    }

    case GateType::GATE_NOT:
        rGate = new GateNot();
        break;
    case GateType::GATE_EMMITTER:
        rGate = new GateToggle();
        break;
    case GateType::GATE_RECIEVER:
        rGate = new GateReciever();
        break;
    case GateType::GATE_CONST_ACTIVE:
        rGate = new GateReciever();
        break;
    case GateType::GATE_CONST_INACTIVE:
        rGate = new GateReciever();
        break;
    case GateType::GATE_TIMER:
        rGate = new GateTimer();
        break;
    default:
         break;
    }
    rGate->SetPosition(stoi(posX),stoi(posY));

    //Todo read nodes
    nextLine
    while (line == SAVE_TAG_NODE)
    {
        NodeIds nodeInfo = readNode(gateStream);
        nextLine
    }

    return rGate;
}

NodeIds GateReader::readNode(std::ifstream& gateStream)
{
    //read in strings
    std::string id, lId, endTag;
    gateStream >> id >> lId >> endTag;

    //Apply string to nodeInfo
    NodeIds nodeInfo;
    try
    {
        nodeInfo.id = std::stoi(id);
        nodeInfo.linkedId = std::stoi(lId);
    }
    catch (...)
    {
        nodeInfo.id = -1;
        nodeInfo.linkedId = -1;
    }

    return nodeInfo;
}

void GateReader::linkNodes(std::vector<Gate *> gates, std::vector<NodeAndIds> nodes)
{

}

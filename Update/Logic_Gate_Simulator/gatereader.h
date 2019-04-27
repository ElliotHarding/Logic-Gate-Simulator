#ifndef SAVINGTEMPLATES_H
#define SAVINGTEMPLATES_H

#endif // SAVINGTEMPLATES_H

#include <string>
#include <QPoint>
#include <vector>
#include <fstream>

#include "gate.h"
#include "gateand.h"
#include "gatenot.h"
#include "gateor.h"
#include "gateinputbox.h"
#include "gateoutputbox.h"
#include "gatefield.h"

struct GateSaveTemplate
{
    GateType name;
    QPoint position;
    std::vector<NodeSaveTemplate> nodes;

    void out(std::ofstream& file)
    {
        //Add general gate info
        file << "--Gate--"
                with std::to_string(name)
                with std::to_string(position.x())
                with std::to_string(position.y());

        //Add node information
        for (NodeSaveTemplate node : nodes)
        {
            node.out(file);
        }
    }
};

struct GateReader
{
public:
    static std::vector<Gate*> readGates (std::ifstream& gateStream)
    {
        std::vector<Gate*> rGates;

        std::string line;
        gateStream >> line;
        while (line == "--Gate--")
        {
            rGates.push_back(readGate(gateStream));
            gateStream >> line;
        }

        return rGates;
    }

private:
    static Gate* readGate(std::ifstream& gateStream)
    {
        //Get gate header info
        std::string bin, type, posX, posY;
        gateStream >> bin >> type >> posX >> posY;

        //Todo read nodes
        std::string line;
        gateStream >> line;
        while (line == "--Node-")
        {
            Node* n = readNode(gateStream);
        }

        //Set return gate
        Gate* rGate;
        switch((GateType)std::stoi(type))
        {
        case GateType::GATE_AND:
            rGate = new GateAnd();
            break;
        case GateType::GATE_OR:
            rGate = new GateOr();
            break;
        case GateType::GATE_NOT:
            rGate = new GateNot();
            break;
        case GateType::GATE_CUSTOM:
            //rGate = new Gate();
            break;
        case GateType::GATE_EMMITTER:
            rGate = new GateInputBox();
            break;
        case GateType::GATE_RECIEVER:
            rGate = new GateOutputBox();
            break;
        default:
             break;
        }

        rGate->SetPosition(stoi(posX),stoi(posY));



        return rGate;
    }

    static Node* readNode(std::ifstream& gateStream)
    {
        return new Node(nullptr);//todo
    }
};



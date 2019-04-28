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
#include "gatecollection.h"

struct GateReader
{
public:

    GateCollection* read(std::ifstream& gateStream)
    {
        std::string header, width, height;
        gateStream >> header >> width >> height;

        return new GateCollection(readGates(gateStream),stoi(width), stoi(height));
    }

    std::vector<Gate*> readGates (std::ifstream& gateStream)
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
    Gate* readGate(std::ifstream& gateStream)
    {
        //Get gate header info
        std::string type, posX, posY;
        gateStream >> type >> posX >> posY;

        //Todo read nodes
        std::string line;
        gateStream >> line;
        while (line == "--Node-")
        {
            readNode(gateStream);
            gateStream >> line;
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

    Node* readNode(std::ifstream& gateStream)
    {
        std::string id, posX, posY, lId;
        gateStream >> id >> posX >> posY >> lId;
        return new Node(nullptr);//todo
    }
};



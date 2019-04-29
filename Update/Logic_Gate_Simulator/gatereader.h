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

    std::vector<Gate*> readGateFieldGates(std::ifstream& gateStream)
    {
        std::vector<Gate*> gates;

        std::string line;
        gateStream >> line;
        if(line == SAVE_TAG_GATE_FIELD)
        {
            gateStream >> line;
            while(line == SAVE_TAG_GATE || line == SAVE_TAG_GATE_COLLECTION)
            {
                if(line == SAVE_TAG_GATE_COLLECTION)
                    gates.push_back(readGateCollection(gateStream));

                else if (line == SAVE_TAG_GATE)
                    gates.push_back(readGate(gateStream));

                gateStream >> line;
            }
        }

        return gates;
    }

    GateCollection* readGateCollection(std::ifstream& gateStream)
    {
        std::vector<Gate*> rGates;
        std::string line;
        gateStream >> line;

        //Some calling functions have already read this,
        //so only goto next line if needed
        if (line == SAVE_TAG_GATE_COLLECTION)
            gateStream >> line;

        //Get all gates inside gate collection tags
        while (line == SAVE_TAG_GATE)
        {
            rGates.push_back(readGate(gateStream));
            gateStream >> line;
        }

        return new GateCollection(rGates);
    }

private:

    Gate* readGate(std::ifstream& gateStream)
    {
        //Get gate header info
        std::string type, posX, posY;
        gateStream >> type >> posX >> posY;

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
        case GateType::GATE_NOT:
            rGate = new GateNot();
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

        //Todo read nodes
        std::string line;
        gateStream >> line;
        while (line == SAVE_TAG_NODE)
        {
            readNode(gateStream);
            gateStream >> line;
        }

        return rGate;
    }

    Node* readNode(std::ifstream& gateStream)
    {
        std::string id, lId, endTag;
        gateStream >> id >> lId >> endTag;
        return new Node(nullptr);//todo
    }
};



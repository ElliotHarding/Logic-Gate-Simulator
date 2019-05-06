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
#include "GateToggle.h"
#include "GateReciever.h"
#include "gatefield.h"
#include "gatecollection.h"

#define nextLine gateStream >> line;

struct GateReader
{
public:

    void readInGateFieldGates(std::ifstream& gateStream, GateField* gf)
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

    GateCollection* readGateCollection(std::ifstream& gateStream)
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

private:

    Gate* readGate(std::ifstream& gateStream, std::string& line)
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
            readNode(gateStream);
            nextLine
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



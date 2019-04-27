#ifndef SAVINGTEMPLATES_H
#define SAVINGTEMPLATES_H

#endif // SAVINGTEMPLATES_H

#include <string>
#include <QPoint>
#include <vector>

struct NodeSaveTemplate
{
    int id;
    QPoint position;
    int linkedNodeId;
};

struct GateSaveTemplate
{
    std::string type;
    QPoint position;
    std::vector<NodeSaveTemplate> nodes;
};

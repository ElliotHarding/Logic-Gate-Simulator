#ifndef GATE_H
#define GATE_H

#include "gameobject.h"
#include "node.h"

class Gate : public DragableGameObject
{
public:
    Gate(const char* iconLocation, int height, int width);

    virtual bool UpdateDrag(int clickX, int clickY);
    virtual void UpdateOutput();

    virtual Node* GetClickNode(int clickX, int clickY) = 0;
};

#endif // GATE_H

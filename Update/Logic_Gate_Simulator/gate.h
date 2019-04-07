#ifndef GATE_H
#define GATE_H

#include "gameobject.h"

class Gate : public DragableGameObject
{
public:
    Gate(const char* iconLocation, int height, int width);

    virtual void UpdateDrag(int clickX, int clickY);
    virtual void UpdateOutput();
};

#endif // GATE_H

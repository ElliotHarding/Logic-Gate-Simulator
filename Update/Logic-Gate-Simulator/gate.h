#ifndef GATE_H
#define GATE_H

#include "gameobject.h"

class Gate : GameObject
{
public:
    Gate(char* iconLocation, int posX, int posY, int height, int width);

    virtual void UpdatePositions(int clickX, int clickY);
    virtual void UpdateOutput();

protected:
    using GameObject::pointInside;
};

#endif // GATE_H

#ifndef GATE_H
#define GATE_H

#include <qobject.h>

class Gate : QObject
{
public:
    Gate();

    virtual void Update(int clickX, int clickY);

    int posX;
    int posY;

    int height;
    int width;

private:
    const int hitboxX = 5;
    const int hitboxY = 5;

    bool pointInside(int x, int y);
};

#endif // GATE_H

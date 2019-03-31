#include "gate.h"

Gate::Gate()
{

}

void Gate::Update(int clickX, int clickY)
{
    if(pointInside(clickX,clickY))
    {
        posX = clickX;
        posY = clickY;
    }
}

bool Gate::pointInside(int x, int y)
{
    if(x > posX - hitboxX && x < posX + hitboxX)
    {
        if(x > posX - hitboxY && x < posX + hitboxY)
        {
            return true;
        }
    }
    return false;
}

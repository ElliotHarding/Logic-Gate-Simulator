#include "gate.h"

Gate::Gate(const char* iconLocation, int height, int width) :
    DragableGameObject::DragableGameObject(iconLocation,height,width)
{
}

bool Gate::UpdateDrag(int clickX, int clickY)
{
    return DragableGameObject::UpdateDrag(clickX, clickY);
}

void Gate::UpdateOutput()
{

}

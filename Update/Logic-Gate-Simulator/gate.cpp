#include "gate.h"

Gate::Gate(char* iconLocation, int height, int width) :
    DragableGameObject::DragableGameObject(iconLocation,height,width)
{
}

void Gate::UpdateDrag(int clickX, int clickY)
{
    DragableGameObject::UpdateDrag(clickX, clickY);
}

void Gate::UpdateOutput()
{

}

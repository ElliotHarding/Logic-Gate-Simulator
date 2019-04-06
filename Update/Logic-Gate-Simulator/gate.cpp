#include "gate.h"

Gate::Gate(char* iconLocation, int posX, int posY, int height, int width) :
    GameObject::GameObject(iconLocation,posX,posY,height,width)
{

}

//ONLY ONE THING CAN BE CLICKED AT A TIME AND NODE SHOULD GO FIRST

void Gate::UpdatePositions(int clickX, int clickY)
{
    //Drag
    if(pointInside(clickX,clickY))
    {
        posX = clickX;
        posY = clickY;
    }

    GameObject::UpdatePositions(clickX,clickY);
}

void Gate::UpdateOutput()
{

}

#include "gameobject.h"

GameObject::GameObject(char* iconLocation, int height_, int width_)
{
    m_icon = QIcon(iconLocation);
    height = height_;
    width = width_;
}

bool GameObject::UpdateClicked(int clickX, int clickY)
{
    beingClicked = pointInside(clickX,clickY);
    return beingClicked;
}

bool GameObject::pointInside(int x, int y)
{
    if(x > posX - m_hitboxX && x < posX + m_hitboxX)
    {
        if(y > posY - m_hitboxY && y < posY + m_hitboxY)
        {
            return true;
        }
    }
    return false;
}

DragableGameObject::DragableGameObject(char *iconLocation, int height, int width) :
    GameObject::GameObject (iconLocation, height, width)
{
}

void DragableGameObject::UpdateDrag(int clickX, int clickY)
{
    //Drag
    if(pointInside(clickX,clickY))
    {
        posX = clickX;
        posY = clickY;
    }
}

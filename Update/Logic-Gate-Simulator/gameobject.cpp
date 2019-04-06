#include "gameobject.h"

GameObject::GameObject(char* iconLocation, int posX_, int posY_, int height_, int width_)
{
    m_icon = QIcon(iconLocation);
    posX = posX_;
    posY = posY_;
    height = height_;
    width = width_;
}

void GameObject::UpdatePositions(int clickX, int clickY)
{

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

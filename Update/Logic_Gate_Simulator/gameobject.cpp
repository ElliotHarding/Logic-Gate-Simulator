#include "gameobject.h"

GameObject::GameObject(const char* iconLocation, int height_, int width_)
{
    m_image = QImage(iconLocation);
    m_height = height_;
    m_width = width_;
}

GameObject::~GameObject()
{

}

void GameObject::UpdateGraphics(QPainter *painter)
{
    QRect rect;
    rect.setX(this->posX);
    rect.setY(this->posY);
    rect.setWidth(m_width);
    rect.setHeight(m_height);

    painter->drawImage(rect,m_image);
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

DragableGameObject::DragableGameObject(const char *iconLocation, int height, int width) :
    GameObject::GameObject (iconLocation, height, width)
{
}

bool DragableGameObject::UpdateDrag(int clickX, int clickY)
{
    //Drag
    if(pointInside(clickX,clickY))
    {
        posX = clickX;
        posY = clickY;
        return true;
    }
    return false;
}

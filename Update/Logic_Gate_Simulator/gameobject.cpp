#include "gameobject.h"

GameObject::GameObject(const char* iconLocation, int width, int height)
{
    m_image = QImage(iconLocation);
    m_width = width;
    m_height = height;
    setPosition(0,0);
}

GameObject::~GameObject()
{

}

void GameObject::UpdateGraphics(QPainter *painter)
{
    painter->drawImage(m_layout,m_image);
}

bool GameObject::UpdateClicked(int clickX, int clickY)
{
    beingClicked = pointInside(clickX,clickY);
    return beingClicked;
}

void GameObject::setPosition(int x, int y)
{
    m_layout.setLeft(x);
    m_layout.setTop(y);
    m_layout.setRight(x + m_width);
    m_layout.setBottom(y + m_height);
}

bool GameObject::pointInside(int x, int y)
{
    if(x > m_layout.x() && x < m_layout.x() + m_layout.width())
    {
        if(y > m_layout.y() && y < m_layout.y() + m_layout.height())
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
    if(UpdateClicked(clickX, clickY))
    {
        setPosition(clickX - m_width/2,clickY - m_height/2);
        return true;
    }
    return false;
}

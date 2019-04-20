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
   return m_layout.contains(QPoint(clickX,clickY));
}

void GameObject::setPosition(int x, int y)
{
    m_layout.setLeft(x - m_width/2);
    m_layout.setTop(y - m_height/2);
    m_layout.setRight(x + m_width/2);
    m_layout.setBottom(y + m_height/2);
}



//
//          DragableGameObject
//

DragableGameObject::DragableGameObject(const char *iconLocation, int height, int width) :
    GameObject::GameObject (iconLocation, height, width)
{
}

bool DragableGameObject::UpdateDrag(int clickX, int clickY)
{
    //Need to specify GameObject::UpdateClicked because overriding function GateInputBox::UpdateClicked
    //Causes its output state to toggle (and we dont want it toggling on and off while dragging it)
    if(GameObject::UpdateClicked(clickX, clickY))
    {
        setPosition(clickX,clickY);
        return true;
    }
    return false;
}

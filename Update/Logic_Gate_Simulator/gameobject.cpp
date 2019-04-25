#include "gameobject.h"

GameObject::GameObject(int width, int height, const char* iconLocation)
{
    if(iconLocation != nullptr)
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
    bool returnVal;

    mutex_contains.lock();
        returnVal = m_layout.contains(QPoint(clickX,clickY));
    mutex_contains.unlock();

    return returnVal;
}

void GameObject::setPosition(int x, int y)
{
    mutex_setPosition.lock();
        m_layout.setLeft(x - m_width/2);
        m_layout.setTop(y - m_height/2);
        m_layout.setRight(x + m_width/2);
        m_layout.setBottom(y + m_height/2);
    mutex_setPosition.unlock();
}

QPoint GameObject::GetPosition()
{
    QPoint returnVal;
    mutex_getPosition.lock();
        returnVal = QPoint(m_layout.x(),m_layout.y());
    mutex_getPosition.unlock();
    return returnVal;
}



//
//          DragableGameObject
//

DragableGameObject::DragableGameObject(int height, int width, const char *iconLocation) :
    GameObject::GameObject (height, width, iconLocation)
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

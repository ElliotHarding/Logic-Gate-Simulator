#include "gameobject.h"

GameObject::GameObject(const uint& x, const uint& y, const uint& width, const uint& height, const char* pIconLocation) :
    m_geometry(x, y, width, height)
{
    if(pIconLocation != nullptr)
        m_image = QImage(pIconLocation);
}

bool GameObject::checkClicked(const int &x, const int &y)
{
    return !m_bUserDisabled && m_geometry.contains(QPoint(x,y));
}

void GameObject::setPosition(const int& x, const int& y)
{
    m_geometry = QRect(x, y, m_geometry.width(), m_geometry.height());
}

void GameObject::draw(QPainter& painter)
{
    painter.drawImage(m_geometry, m_image);
}

void GameObject::setUserDisabled()
{
    m_bUserDisabled = true;
}

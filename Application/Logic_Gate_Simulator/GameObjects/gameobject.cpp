#include "gameobject.h"

GameObject::GameObject(const uint& x, const uint& y, const uint& width, const uint& height, const char* pIconLocation) :
    m_geometry(x, y, width, height)
{
    if(pIconLocation != nullptr)
        m_image = QImage(pIconLocation);
}

GameObject::~GameObject()
{
}

bool GameObject::checkClicked(const int &x, const int &y)
{
    return m_geometry.contains(QPoint(x,y));
}

void GameObject::setPosition(const int& x, const int& y)
{
    m_geometry = QRect(x, y, m_geometry.width(), m_geometry.height());
}

void GameObject::setUserDisabled()
{
    m_bUserDisabled = true;
}

void GameObject::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.drawImage(QRect(0, 0, geometry().width(), geometry().height()), m_image);
}

void GameObject::mousePressEvent(QMouseEvent*)
{
    if(!m_bUserDisabled)
    {
        emit onClicked(this);
    }
}

void GameObject::mouseReleaseEvent(QMouseEvent*)
{
    if(!m_bUserDisabled)
    {
        emit onReleased(this);
    }
}

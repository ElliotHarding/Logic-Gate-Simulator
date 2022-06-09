#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QMouseEvent>

class GameObject : public QWidget
{
    Q_OBJECT

public:
    GameObject(QWidget* pParent, const uint& x, const uint& y, const uint& width, const uint& height, const char* pIconLocation = nullptr);
    ~GameObject();

    virtual void setPosition(const uint& x, const uint& y);

    void setUserDisabled();

signals:
    void onClicked(GameObject* pGo);
    void onReleased(GameObject* pGo);

protected:
    void paintEvent(QPaintEvent* paintEvent) override;
    void mousePressEvent(QMouseEvent* mouseEvent) override;
    void mouseReleaseEvent(QMouseEvent* mouseEvent) override;

private:
    QImage m_image;

    bool m_bUserDisabled = false;
};

#endif // GAMEOBJECT_H

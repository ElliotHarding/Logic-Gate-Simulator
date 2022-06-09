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
    GameObject(QWidget* pParent, int width, int height, const char* iconLocation = nullptr);
    ~GameObject();

    void SetUserDisabled();

protected:
    void paintEvent(QPaintEvent* paintEvent) override;
    void mousePressEvent(QMouseEvent* mouseEvent) override;

private:
    QImage m_image;

    bool m_bUserDisabled = false;
};

#endif // GAMEOBJECT_H

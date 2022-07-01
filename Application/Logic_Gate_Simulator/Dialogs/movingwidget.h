#ifndef MOVINGWIDGET_H
#define MOVINGWIDGET_H

#include <QWidget>

class DLG_Home;

class MovingWidget : public QWidget
{
public:
    MovingWidget(DLG_Home *parent, bool show = false, QPoint loc = QPoint(0,0));
    ~MovingWidget();

    virtual void show(){ QWidget::show(); }

protected:
    DLG_Home* m_pParent;

    QPoint spawnPosition(const QPoint& buttonPoint) const;
};

#endif // MOVINGWIDGET_H

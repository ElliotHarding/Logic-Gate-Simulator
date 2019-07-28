#ifndef MOVINGWIDGET_H
#define MOVINGWIDGET_H

#include "gatetypes.h"
#include <QWidget>

class DLG_Home;

class MovingWidget : public QWidget
{
public:
    MovingWidget(DLG_Home *parent, bool show = false, QPoint loc = QPoint(0,0));
    ~MovingWidget();

protected:
    DLG_Home* m_pParent;
};

#endif // MOVINGWIDGET_H

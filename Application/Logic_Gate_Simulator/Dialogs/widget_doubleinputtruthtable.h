#ifndef WIDGET_DOUBLEINPUTTRUTHTABLE_H
#define WIDGET_DOUBLEINPUTTRUTHTABLE_H

#include <QWidget>

namespace Ui {
class Widget_DoubleInputTruthTable;
}

class Widget_DoubleInputTruthTable : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_DoubleInputTruthTable(QWidget *parent = nullptr);
    ~Widget_DoubleInputTruthTable();

private:
    Ui::Widget_DoubleInputTruthTable *ui;
};

#endif // WIDGET_DOUBLEINPUTTRUTHTABLE_H

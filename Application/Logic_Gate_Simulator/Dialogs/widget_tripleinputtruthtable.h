#ifndef WIDGET_TRIPLEINPUTTRUTHTABLE_H
#define WIDGET_TRIPLEINPUTTRUTHTABLE_H

#include <QWidget>

namespace Ui {
class Widget_TripleInputTruthTable;
}

class Widget_TripleInputTruthTable : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_TripleInputTruthTable(QWidget *parent = nullptr);
    ~Widget_TripleInputTruthTable();

private:
    Ui::Widget_TripleInputTruthTable *ui;
};

#endif // WIDGET_TRIPLEINPUTTRUTHTABLE_H

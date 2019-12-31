#ifndef WIDGET_DOUBLEINPUTTRUTHTABLE_H
#define WIDGET_DOUBLEINPUTTRUTHTABLE_H

#include <QWidget>
#include "truthtablewidgetbase.h"

namespace Ui {
class Widget_DoubleInputTruthTable;
}

struct DoubleInputTruthTable
{
public:
    static const int size = 4;
    bool inputA[size] = {0,1,0,1};
    bool inputB[size] = {0,0,1,1};
    bool output[size];
};

class Widget_DoubleInputTruthTable : public TruthTableWidgetBase
{
    Q_OBJECT

public:
    explicit Widget_DoubleInputTruthTable(QWidget *parent = nullptr);
    ~Widget_DoubleInputTruthTable();

    void SetResults(bool results[]);
    std::vector<bool> GetResults();

private:
    Ui::Widget_DoubleInputTruthTable *ui;
    void DisableTextEdit();
};

#endif // WIDGET_DOUBLEINPUTTRUTHTABLE_H

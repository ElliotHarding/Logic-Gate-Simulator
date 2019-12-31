#ifndef WIDGET_TRIPLEINPUTTRUTHTABLE_H
#define WIDGET_TRIPLEINPUTTRUTHTABLE_H

#include <QWidget>
#include "truthtablewidgetbase.h"

namespace Ui {
class Widget_TripleInputTruthTable;
}

struct TripleInputTruthTable
{
public:
    static const int size = 8;
    bool inputA[size] = {0,0,0,0,1,1,1,1};
    bool inputB[size] = {0,0,1,1,0,0,1,1};
    bool inputC[size] = {0,1,0,1,0,1,0,1};
    bool output[size];
};

class Widget_TripleInputTruthTable : public TruthTableWidgetBase
{
    Q_OBJECT

public:
    explicit Widget_TripleInputTruthTable(QWidget *parent = nullptr);
    ~Widget_TripleInputTruthTable();

    void SetResults(bool results[]);
    std::vector<bool> GetAnswer();

private:
    Ui::Widget_TripleInputTruthTable *ui;
    void DisableTextEdit();

    BinaryLabel* m_pLblResult1;
    BinaryLabel* m_pLblResult2;
    BinaryLabel* m_pLblResult3;
    BinaryLabel* m_pLblResult4;
    BinaryLabel* m_pLblResult5;
    BinaryLabel* m_pLblResult6;
    BinaryLabel* m_pLblResult7;
    BinaryLabel* m_pLblResult8;
};

#endif // WIDGET_TRIPLEINPUTTRUTHTABLE_H

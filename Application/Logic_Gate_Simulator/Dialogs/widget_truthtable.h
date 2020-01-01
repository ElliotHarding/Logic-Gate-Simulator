#ifndef WIDGET_TRUTHTABLE_H
#define WIDGET_TRUTHTABLE_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class Widget_TruthTable;
}

class BinaryLabel;

/*
struct TripleInputTruthTable
{
public:
    static const int size = 8;
    bool inputA[size] = {0,0,0,0,1,1,1,1};
    bool inputB[size] = {0,0,1,1,0,0,1,1};
    bool inputC[size] = {0,1,0,1,0,1,0,1};
    bool output[size];
};

struct DoubleInputTruthTable
{
public:
    static const int size = 4;
    bool inputA[size] = {0,1,0,1};
    bool inputB[size] = {0,0,1,1};
    bool output[size];
};
*/

class Widget_TruthTable : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_TruthTable(int iInputs, int iOutputs, QWidget *parent = nullptr);
    ~Widget_TruthTable();

    void SetResults(std::vector<std::vector<bool>> results);
    std::vector<std::vector<bool>> GetAnswer();

private:
    Ui::Widget_TruthTable *ui;
    void DisableTextEdit();

    std::vector<std::vector<BinaryLabel*>> m_resultLabels;
    std::vector<QLabel*> m_labelBin;
};

class BinaryLabel : public QLabel
{
    Q_OBJECT

public:
    BinaryLabel(QWidget *parent = nullptr);

    void SetValue(bool value);
    bool GetValue();
    void Disable();

protected:
    void mousePressEvent(QMouseEvent *ev) override;

    bool m_bDisabled = false;
};

#endif // WIDGET_TRUTHTABLE_H

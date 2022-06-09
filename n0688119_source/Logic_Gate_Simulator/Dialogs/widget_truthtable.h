#ifndef WIDGET_TRUTHTABLE_H
#define WIDGET_TRUTHTABLE_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class Widget_TruthTable;
}

class BinaryLabel;

static const std::vector<std::vector<bool>> valuesFor4inputs =
{
    {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1},
    {0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1},
    {0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1},
    {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1}
};

static const std::vector<std::vector<bool>> valuesFor3inputs =
{
    {0,0,0,0,1,1,1,1},
    {0,0,1,1,0,0,1,1},
    {0,1,0,1,0,1,0,1}
};

static const std::vector<std::vector<bool>> valuesFor2inputs =
{
    {0,0,1,1},
    {0,1,0,1}
};

static const std::vector<std::vector<bool>> valuesFor1inputs =
{
    {0,1}
};

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

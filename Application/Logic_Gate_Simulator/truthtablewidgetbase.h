#ifndef TRUTHTABLEWIDGETBASE_H
#define TRUTHTABLEWIDGETBASE_H

#include "vector"
#include <QWidget>
#include <QLabel>

class TruthTableWidgetBase : public QWidget
{
    Q_OBJECT

public:
    TruthTableWidgetBase(QWidget *parent = nullptr);

    virtual void SetResults(bool results[]) = 0;
    virtual std::vector<bool> GetResults() = 0;
    //virtual void DisableTextEdit(bool disableTextEdit) = 0;
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

#endif // TRUTHTABLEWIDGETBASE_H

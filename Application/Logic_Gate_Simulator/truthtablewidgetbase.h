#ifndef TRUTHTABLEWIDGETBASE_H
#define TRUTHTABLEWIDGETBASE_H

#include "vector"
#include <QWidget>

class TruthTableWidgetBase : public QWidget
{
    Q_OBJECT

public:
    TruthTableWidgetBase(QWidget *parent = nullptr);

    virtual void SetResults(bool results[]) = 0;
    virtual std::vector<bool> GetResults() = 0;
    //virtual void DisableTextEdit(bool disableTextEdit) = 0;
};

#endif // TRUTHTABLEWIDGETBASE_H

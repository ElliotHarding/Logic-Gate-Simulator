#ifndef DLG_BOOLEANEXPRESSIONS_H
#define DLG_BOOLEANEXPRESSIONS_H

#include <QDialog>
#include "truthtable.h"

namespace Ui {
class DLG_BooleanExpressions;
}

class DLG_BooleanExpressions : public QDialog
{
    Q_OBJECT

public:
    explicit DLG_BooleanExpressions(QWidget *parent = nullptr);
    ~DLG_BooleanExpressions();

    void showExpressions(const std::vector<BooleanExpression>& expressions);

private slots:
    void on_btn_ok_clicked();

private:
    Ui::DLG_BooleanExpressions *ui;
};

#endif // DLG_BOOLEANEXPRESSIONS_H

#ifndef DLG_BOOLEANEXPRESSIONS_H
#define DLG_BOOLEANEXPRESSIONS_H

#include <QDialog>

namespace Ui {
class DLG_BooleanExpressions;
}

class BooleanExpression;

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

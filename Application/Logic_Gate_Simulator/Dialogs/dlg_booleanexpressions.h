#ifndef DLG_BOOLEANEXPRESSIONS_H
#define DLG_BOOLEANEXPRESSIONS_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>

namespace Ui {
class DLG_BooleanExpressions;
}

class BooleanExpression;
class BooleanExpressionDisplay;

///////////////////////////////////////////////////////////////////////////////////////
/// \brief The DLG_BooleanExpressions class
///
class DLG_BooleanExpressions : public QDialog
{
    Q_OBJECT

public:
    explicit DLG_BooleanExpressions(QWidget *parent = nullptr);
    ~DLG_BooleanExpressions();

    void showExpressions(const std::vector<BooleanExpression>& expressions);

protected:
    void closeEvent(QCloseEvent *) override;

private slots:
    void on_btn_ok_clicked();
    void on_btn_genCircuit_clicked();
    void on_btn_genTruthTable_clicked();

private:
    Ui::DLG_BooleanExpressions *ui;

    ///Boolean letters
    std::vector<BooleanExpressionDisplay*> m_uiExpressions;
    std::vector<QLabel*> m_uiResultLabels;
    void clear();
};

///////////////////////////////////////////////////////////////////////////////////////
/// \brief The BooleanExpressionDisplay class
///
class BooleanExpressionDisplay : public QLineEdit
{
    Q_OBJECT
public:
    BooleanExpressionDisplay(QWidget* pParent, const BooleanExpression& expression);

    BooleanExpression getExpression();

protected:
    void mousePressEvent(QMouseEvent* mouseEvent) override;
    void paintEvent(QPaintEvent* paintEvent) override;

private:
    std::vector<bool> m_invertedLetters;
};

#endif // DLG_BOOLEANEXPRESSIONS_H

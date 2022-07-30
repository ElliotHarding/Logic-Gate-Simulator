#ifndef DLG_BOOLEANEXPRESSIONS_H
#define DLG_BOOLEANEXPRESSIONS_H

#include "truthtable.h"

#include <QDialog>
#include <QLineEdit>
#include <QLabel>

namespace Ui {
class DLG_BooleanExpressions;
}

class BooleanExpressionDisplay;
class QListWidgetItem;

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
    void removeUiExpression(QListWidgetItem* pItem);

protected:
    void closeEvent(QCloseEvent *) override;

private slots:
    void on_btn_ok_clicked();
    void on_btn_genCircuit_clicked();
    void on_btn_genTruthTable_clicked();

    void on_btn_addExpression_clicked();

private:
    Ui::DLG_BooleanExpressions *ui;

    ///Boolean letters
    void addUiExpression(const BooleanExpression& expression);
    void clear();
};

///////////////////////////////////////////////////////////////////////////////////////
/// \brief The BooleanExpressionDisplay class
///
class BooleanExpressionDisplay : public QWidget
{
    Q_OBJECT
public:
    BooleanExpressionDisplay(DLG_BooleanExpressions* pParent, QListWidgetItem* m_pListWidgetItem, const BooleanExpression& expression, const QRect& geometry);
    ~BooleanExpressionDisplay();

    BooleanExpression getExpression();

protected:
    void mousePressEvent(QMouseEvent* mouseEvent) override;
    void paintEvent(QPaintEvent* paintEvent) override;

private slots:
    void onRemoveButtonClicked();

private:
    DLG_BooleanExpressions* m_pParent;

    QListWidgetItem* m_pListWidgetItem;

    BooleanExpression m_expression;

    QPushButton* m_pRemoveBtn;
};

#endif // DLG_BOOLEANEXPRESSIONS_H

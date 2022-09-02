#ifndef DLG_BOOLEANEXPRESSIONS_H
#define DLG_BOOLEANEXPRESSIONS_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>

namespace Ui {
class DLG_BooleanExpressions;
}

class BooleanExpressionDisplay;
class QListWidgetItem;
class DLG_Home;
class GateCollection;
struct BooleanExpression;

///////////////////////////////////////////////////////////////////////////////////////
/// \brief The DLG_BooleanExpressions class
///
class DLG_BooleanExpressions : public QDialog
{
    Q_OBJECT

public:
    explicit DLG_BooleanExpressions(DLG_Home* pHome);
    ~DLG_BooleanExpressions();

    void open();
    void showExpressions(const std::vector<BooleanExpression>& expressions);
    void removeUiExpression(QListWidgetItem* pItem);

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

    DLG_Home* m_pHome;
};

/////////////////////////////////////////////////////////////////////////////////////////
/// \brief The BooleanExpressionLineEdit class
///
class BooleanExpressionLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    BooleanExpressionLineEdit(QWidget* pParent, const BooleanExpression& expression, DLG_BooleanExpressions* pDlgExpressions);

    BooleanExpression getExpression();

private:
    DLG_BooleanExpressions* m_pDlgExpressions;
};

///////////////////////////////////////////////////////////////////////////////////////
/// \brief The BooleanExpressionDisplay class
///
class BooleanExpressionDisplay : public QWidget
{
    Q_OBJECT
public:
    BooleanExpressionDisplay(DLG_BooleanExpressions* pParent, QListWidgetItem* m_pListWidgetItem, const BooleanExpression& expression);
    ~BooleanExpressionDisplay();

    BooleanExpression getExpression();

    void updateResultLetter(const char& resultLetter);

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private slots:
    void onRemoveButtonClicked();

private:
    DLG_BooleanExpressions* m_pParent;

    QListWidgetItem* m_pListWidgetItem;

    char m_resultLetter;

    QPushButton* m_pRemoveBtn;
    BooleanExpressionLineEdit* m_pExpressionText;
    QLabel* m_pResultLabel;
};

#endif // DLG_BOOLEANEXPRESSIONS_H

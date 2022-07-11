#ifndef DLG_BOOLEANEXPRESSIONS_H
#define DLG_BOOLEANEXPRESSIONS_H

#include <QDialog>

namespace Ui {
class DLG_BooleanExpressions;
}

class BooleanExpression;
class BooleanExpressionLetter;

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

private slots:
    void on_btn_ok_clicked();

private:
    Ui::DLG_BooleanExpressions *ui;

    std::vector<BooleanExpressionLetter*> m_booleanLetters;
};

///////////////////////////////////////////////////////////////////////////////////////
/// \brief The BooleanExpressionLetter class
///
class BooleanExpressionLetter : public QWidget
{
    Q_OBJECT
public:
    BooleanExpressionLetter(QWidget* pParent, const QString& letter, const bool& inverted, const bool& editable);

protected:
    void mousePressEvent(QMouseEvent* mouseEvent) override;
    void paintEvent(QPaintEvent* paintEvent) override;

private:
    QString m_letter;
    bool m_bInverted;
    bool m_bEditable;
};

#endif // DLG_BOOLEANEXPRESSIONS_H

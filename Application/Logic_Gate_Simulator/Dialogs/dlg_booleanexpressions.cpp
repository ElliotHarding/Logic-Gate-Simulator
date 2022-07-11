#include "dlg_booleanexpressions.h"
#include "ui_dlg_booleanexpressions.h"

#include "truthtable.h"

DLG_BooleanExpressions::DLG_BooleanExpressions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DLG_BooleanExpressions)
{
    ui->setupUi(this);
}

DLG_BooleanExpressions::~DLG_BooleanExpressions()
{
    delete ui;
}

void DLG_BooleanExpressions::showExpressions(const std::vector<BooleanExpression>& expressions)
{
    //Temp stuff
    //Todo ~ make editable
    //Todo ~ make dynamic sized

    QString resultsText = "";
    QString expresionsText = "";

    for(uint iExpression = 0; iExpression < expressions.size(); iExpression++)
    {
        QString invertedString = "";
        QString inputsString = "";
        for(uint iInverted = 0; iInverted < expressions[iExpression].inverted.size(); iInverted++)
        {
            invertedString += expressions[iExpression].inverted[iInverted] ? "_" : " ";
            inputsString += expressions[iExpression].letters[iInverted];
        }

        expresionsText += invertedString + "\n" + inputsString + "\n";
        resultsText += "\n = " + QString(expressions[iExpression].resultLetter) + "\n";
    }

    ui->lbl_expressions->setText(expresionsText);
    ui->lbl_results->setText(resultsText);

    open();
}

void DLG_BooleanExpressions::on_btn_ok_clicked()
{
    close();
}

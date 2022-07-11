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
        QString lettersString = "";
        for(uint iLetter = 0; iLetter < expressions[iExpression].letters.size(); iLetter++)
        {
            invertedString += expressions[iExpression].inverted[iLetter] ? "_" : " ";
            lettersString += expressions[iExpression].letters[iLetter];
        }

        expresionsText += invertedString + "\n" + lettersString + "\n";
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

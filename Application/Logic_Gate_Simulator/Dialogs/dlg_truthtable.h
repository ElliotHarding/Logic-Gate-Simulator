#ifndef DLG_TRUTHTABLE_H
#define DLG_TRUTHTABLE_H

#include "truthtable.h"

#include <QDialog>
#include <QLabel>

namespace Ui {
class DLG_TruthTable;
}

class DLG_Home;

class DLG_TruthTable : public QDialog
{
    Q_OBJECT

public:
    explicit DLG_TruthTable(DLG_Home* pParent);
    ~DLG_TruthTable();

    //Open to display truth table
    void open(const TruthTable& truthTable);
    void close();

protected:
    void closeEvent(QCloseEvent *) override;

private slots:
    void on_btn_circuit_clicked();

    void on_btn_expressions_clicked();

private:
    Ui::DLG_TruthTable *ui;
    std::vector<QLabel*> m_tableLabels;

    TruthTable m_truthTable;

    DLG_Home* m_pHome;
};

#endif // DLG_TRUTHTABLE_H

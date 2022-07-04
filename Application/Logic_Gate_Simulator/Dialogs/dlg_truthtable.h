#ifndef DLG_TRUTHTABLE_H
#define DLG_TRUTHTABLE_H

#include <QDialog>

namespace Ui {
class DLG_TruthTable;
}

class DLG_TruthTable : public QDialog
{
    Q_OBJECT

public:
    explicit DLG_TruthTable(QWidget *parent = nullptr);
    ~DLG_TruthTable();

private:
    Ui::DLG_TruthTable *ui;
};

#endif // DLG_TRUTHTABLE_H

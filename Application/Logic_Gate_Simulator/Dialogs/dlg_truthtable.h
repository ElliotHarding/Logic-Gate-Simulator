#ifndef DLG_TRUTHTABLE_H
#define DLG_TRUTHTABLE_H

#include "truthtable.h"

#include <QDialog>
#include <QLabel>

namespace Ui {
class DLG_TruthTable;
}

class BinaryLabel;

class DLG_TruthTable : public QDialog
{
    Q_OBJECT

public:
    explicit DLG_TruthTable(QWidget* pParent);
    ~DLG_TruthTable();

    //Open to display truth table
    void open(const TruthTable& truthTable);
    void close();

private:
    Ui::DLG_TruthTable *ui;
    std::vector<QLabel*> m_tableLabels;
};

#endif // DLG_TRUTHTABLE_H

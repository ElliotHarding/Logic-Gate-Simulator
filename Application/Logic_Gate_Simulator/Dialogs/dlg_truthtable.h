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
    explicit DLG_TruthTable(QWidget *parent = nullptr);
    ~DLG_TruthTable();

    //Open to display truth table
    void open(const TruthTable& truthTable);

    //Open to create new truth table
    void open();

private:
    Ui::DLG_TruthTable *ui;

    std::vector<std::vector<BinaryLabel*>> m_resultLabels;
    std::vector<QLabel*> m_labelBin;
};

class BinaryLabel : public QLabel
{
    Q_OBJECT

public:
    BinaryLabel(QWidget* parent, const bool& value = false, const bool& editDisabled = false);

    bool value();

protected:
    void mousePressEvent(QMouseEvent* event) override;

    bool m_bEditDisabled = false;
};

#endif // DLG_TRUTHTABLE_H

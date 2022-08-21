#ifndef DLG_TRUTHTABLE_H
#define DLG_TRUTHTABLE_H

#include "truthtable.h"

#include <QDialog>
#include <QLabel>

namespace Ui {
class DLG_TruthTable;
}

class DLG_Home;
class CircuitFromTruthTableThread;
class GateCollection;
class OutputLabel;

class DLG_TruthTable : public QDialog
{
    Q_OBJECT

public:
    explicit DLG_TruthTable(DLG_Home* pParent);
    ~DLG_TruthTable();

    //Open to display truth table
    void open(const TruthTable& truthTable);
    void open() override;

protected:
    void closeEvent(QCloseEvent *) override;
    void close();

private slots:
    void on_btn_circuit_clicked();
    void on_btn_expressions_clicked();

    void on_spinBox_inputs_valueChanged(int value);
    void on_spinBox_outputs_valueChanged(int value);

    void onCircuitGenSuccess(GateCollection* pNewCircuit);
    void onCircuitGenFailure(const QString& failMessage);

private:
    void clearUI();
    void updateTableUI();
    void updateTruthTableFromUI();

    Ui::DLG_TruthTable *ui;
    std::vector<QLabel*> m_tableLabels;
    std::vector<std::vector<OutputLabel*>> m_tableOutputLabels;

    TruthTable m_truthTable;

    DLG_Home* m_pHome;

    CircuitFromTruthTableThread* m_pCircuitFromTruthTableThread;
};

//////////////////////////////////////////////////////////
/// \brief The OutputLabel class
///
class OutputLabel : public QLabel
{
    Q_OBJECT
public:
    OutputLabel(DLG_TruthTable* pDlgTruthTable, const bool& value);

    bool value() const;

protected:
    void mousePressEvent(QMouseEvent* event) override;
};

#endif // DLG_TRUTHTABLE_H

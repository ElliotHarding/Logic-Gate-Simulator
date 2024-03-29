#ifndef DLG_EditScript_H
#define DLG_EditScript_H

#include <QDialog>
#include <QFile>
#include <QFileDialog>
#include "gatefpga.h"

namespace Ui {
class DLG_EditScript;
}

class DLG_Home;

//////////////////////////////////////////////////////////////////////////
///DLG_EditScript
class DLG_EditScript : public QDialog
{
    Q_OBJECT

public:
    explicit DLG_EditScript(DLG_Home* pParent);
    ~DLG_EditScript();

    void open(GateFPGA* pFPGA);
    bool close();

private slots:
    void on_spinBox_inputs_valueChanged(int numInputs);
    void on_spinBox_outputs_valueChanged(int numOutputs);

    void on_btn_setScript_clicked();
    void on_btn_genCircuit_clicked();
    void on_btn_genTuthTable_clicked();

private slots:
    void on_btn_load_clicked();
    void on_btn_Save_clicked();

    void on_btn_genExpressions_clicked();

private:
    ///Home & UI
    Ui::DLG_EditScript *ui;
    DLG_Home* m_pHome;
    void setStartScript(const uint& numInputs);
    void setEndScript(const uint& numOutputs);

    GateFPGA* m_pFpga = nullptr;

    ///Saving/loading
    QFileDialog* m_pDlgLoadGates;
    QString m_currentSavePath = "";
    void saveScriptFile(QFile& file, const QString& script, const uint& inputs, const uint& outputs);
};

#endif // DLG_EditScript_H

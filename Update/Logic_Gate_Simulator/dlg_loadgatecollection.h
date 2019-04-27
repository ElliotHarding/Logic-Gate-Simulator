#ifndef DLG_LOADGATECOLLECTION_H
#define DLG_LOADGATECOLLECTION_H

#include <QDialog>
#include "gatefield.h"

namespace Ui {
class DLG_LoadGateCollection;
}

class DLG_LoadGateCollection : public QDialog
{
    Q_OBJECT

public:
    explicit DLG_LoadGateCollection(GateField* currentGateField, QWidget *parent = nullptr);
    ~DLG_LoadGateCollection();

private slots:
    void on_btn_ok_clicked();
    void on_btn_cancel_clicked();

private:
    Ui::DLG_LoadGateCollection *ui;
    GateField* m_currentGateField;
    Gate* m_loadedGateCollection = nullptr;
};

#endif // DLG_LOADGATECOLLECTION_H

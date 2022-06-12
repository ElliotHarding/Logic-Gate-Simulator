#ifndef DLG_SAVEGATECOLLECTION_H
#define DLG_SAVEGATECOLLECTION_H

#include "gatecollection.h"
#include "gatereader.h"

#include <QDialog>

namespace Ui {
class DLG_SaveGateCollection;
}

class DLG_SaveGateCollection : public QDialog
{
    Q_OBJECT

public:
    explicit DLG_SaveGateCollection(DLG_Home *parent = nullptr);
    ~DLG_SaveGateCollection() override;

    void open(GateCollection* pGateCollection);

private slots:
    void on_Cancel_clicked();
    void on_Save_clicked();

private:
    Ui::DLG_SaveGateCollection *ui;
    GateCollection* m_pCurrentGateCollection;
    DLG_Home* m_pParent;
    Saver m_saver;
};

#endif // DLG_SAVEGATECOLLECTION_H

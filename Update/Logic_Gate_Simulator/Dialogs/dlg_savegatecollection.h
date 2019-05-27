#ifndef DLG_SAVEGATECOLLECTION_H
#define DLG_SAVEGATECOLLECTION_H

#include <QDialog>
#include "gatefield.h"

namespace Ui {
class DLG_SaveGateCollection;
}

class DLG_SaveGateCollection : public QDialog
{
    Q_OBJECT

public:
    explicit DLG_SaveGateCollection(QWidget *parent = nullptr);
    ~DLG_SaveGateCollection() override;

    void SetCurrentGateField(GateField* current);
    virtual void open() override;

private slots:
    void on_Cancel_clicked();
    void on_Save_clicked();

private:
    Ui::DLG_SaveGateCollection *ui;
    GateField* m_currentGateField;
};

#endif // DLG_SAVEGATECOLLECTION_H

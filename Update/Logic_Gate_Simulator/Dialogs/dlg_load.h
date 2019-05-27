#ifndef DLG_LOAD_H
#define DLG_LOAD_H

#include <QMainWindow>
#include "dlg_home.h"

namespace Ui {
class DLG_Load;
}

class DLG_Load : public QMainWindow
{
    Q_OBJECT

public:
    explicit DLG_Load(QWidget *parent = nullptr);
    ~DLG_Load() override;

private slots:
    void on_btnLoad_clicked();

private:
    Ui::DLG_Load *ui;
};

#endif // DLG_LOAD_H

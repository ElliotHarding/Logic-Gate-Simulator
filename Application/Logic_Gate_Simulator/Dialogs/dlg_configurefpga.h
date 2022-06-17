#ifndef DLG_CONFIGUREFPGA_H
#define DLG_CONFIGUREFPGA_H

#include <QDialog>

namespace Ui {
class DLG_ConfigureFPGA;
}
class GateFPGA;

class DLG_ConfigureFPGA : public QDialog
{
    Q_OBJECT

public:
    explicit DLG_ConfigureFPGA(QWidget *parent = nullptr);
    ~DLG_ConfigureFPGA();

    void open(GateFPGA* pFPGA);

private:
    Ui::DLG_ConfigureFPGA *ui;

    GateFPGA* m_pFpga = nullptr;
};

#endif // DLG_CONFIGUREFPGA_H

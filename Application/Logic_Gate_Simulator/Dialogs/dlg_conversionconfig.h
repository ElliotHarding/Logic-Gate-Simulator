#ifndef DLG_CONVERSIONCONFIG_H
#define DLG_CONVERSIONCONFIG_H

#include <QDialog>
#include "converter.h"

namespace Ui {
class DLG_ConversionConfig;
}

class DLG_ConversionConfig : public QDialog
{
    Q_OBJECT

public:
    explicit DLG_ConversionConfig(QWidget *parent = nullptr);
    ~DLG_ConversionConfig();

    ConversionAlgorithm getAlgorithm() const;
    CircuitOptions getCircuitGenOptions() const;

protected:
    void closeEvent(QCloseEvent* pEvent) override;

private:
    Ui::DLG_ConversionConfig *ui;
};

#endif // DLG_CONVERSIONCONFIG_H

#ifndef DLG_GATEINFO_H
#define DLG_GATEINFO_H

#include <QWidget>

namespace Ui {
class DLG_GateInfo;
}

class Gate;
class DLG_GateInfo : public QWidget
{
    Q_OBJECT

public:
    explicit DLG_GateInfo(QWidget *parent = nullptr);
    ~DLG_GateInfo();

    void setGate(Gate* g);

private:
    Ui::DLG_GateInfo *ui;
};

#endif // DLG_GATEINFO_H

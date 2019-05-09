#ifndef DLG_GATEINFO_H
#define DLG_GATEINFO_H

#include <QWidget>
#include <QThread>

//Forward declerations
namespace Ui {
class DLG_GateInfo;
}
class DLG_Home;
class Gate;
class InfoUpdateThread;

class DLG_GateInfo : public QWidget
{
    Q_OBJECT

public:
    explicit DLG_GateInfo(DLG_Home* parent = nullptr);
    ~DLG_GateInfo();

    void setGate(Gate* g);
    void RefreshInfo();

private slots:
    void on_checkBox_clicked();
    void on_btn_DeleteGate_clicked();
    void on_lineEdit_Frequency_editingFinished();

    void on_dragModeCheck_clicked();

    void on_signalCheck_clicked();

private:
    Ui::DLG_GateInfo *ui;
    DLG_Home* m_pParent = nullptr;
    Gate* m_gateDisplayed = nullptr;
    bool m_bDragModeAll = true;
    InfoUpdateThread* m_infoUpdateThread;
};


//Update thread for DLG_GateInfo
//------------------------------------
// Runs continuously - for existance of DLG_GateInfo
class InfoUpdateThread : public QThread
{
    Q_OBJECT
public:
    InfoUpdateThread(DLG_GateInfo* parent);
    ~InfoUpdateThread() override;

    void stop();

private:
    void run() override;
    bool m_bStopThread = false;
    DLG_GateInfo* m_pInfoDialog = nullptr;

};

#endif // DLG_GATEINFO_H

#ifndef GATEFPGA_H
#define GATEFPGA_H

#include <QDialog>
#include "gate.h"

class GateFPGA;
class UpdateScript;

class DLG_FPGA : public QDialog
{
public:
    DLG_FPGA(GateFPGA* parent);

    void EditFpgaScript(UpdateScript* pUpdateScript);

protected:
    GateFPGA* m_pParentGate;

};

class UpdateScript
{
public:
    UpdateScript();

    void CalculateOutput(std::vector<Node*>& in, std::vector<Node*>& out);
    void SaveData(std::ofstream& storage);
protected:

};

class GateFPGA : public Gate
{
public:
    GateFPGA(const int& x, const int& y);
    ~GateFPGA();

    virtual void draw(QPainter& painter) override;
    virtual GameObject* checkClicked(const int& x, const int& y) override;
    virtual void UpdateOutput() override;
    virtual void SaveData(std::ofstream& storage) override;
    virtual Gate* Clone() override;

    void OpenEditor();

protected:

    UpdateScript m_updateScript;

    DLG_FPGA* m_pDlgEdit;

    ///Nodes
    std::vector<Node*> m_inputNodes;
    std::vector<Node*> m_outputNodes;
};

#endif // GATEFPGA_H

#ifndef GATEFPGA_H
#define GATEFPGA_H

#include <QDialog>
#include "gate.h"

namespace Settings
{
const QString FPGAGateScriptElement = "Script";
}

class GateFPGA : public Gate
{
public:
    GateFPGA(const int& x = 0, const int& y = 0);
    GateFPGA(std::vector<Node*>& inputNodesToCopy, std::vector<Node*>& outputNodesToCopy, const QString& script, const int& x = 0, const int& y = 0);
    GateFPGA(const QString& script, std::vector<NodeIds>& inputNodeInfo, std::vector<NodeIds>& outputNodeInfo, const int& x, const int& y);
    ~GateFPGA();

    ///Gate class functions
    virtual void draw(QPainter& painter) override;
    virtual void UpdateOutput() override;
    virtual void SaveData(QDomDocument& storage, QDomElement& parentElement) override;
    virtual Gate* Clone() override;

    ///FPGA specific functions
    void OpenEditor();
    void setInputs(const uint& numInputs);
    void setOutputs(const uint& numOutputs);
    uint getNumInputs() const;
    uint getNumOutputs() const;
    std::vector<Node*> getInputNodes() override;
    std::vector<Node*> getOutputNodes() override;
    QString getScript() const;
    void setScript(const QString& script);

protected:

    void updateGeometryBasedOnNodes();

    void eraseNodeFromAllNodes(Node* pNode);

    QRect m_editButtonRect;

    ///Nodes
    std::vector<Node*> m_inputNodes;
    std::vector<Node*> m_outputNodes;

    QString m_script;
};

#endif // GATEFPGA_H

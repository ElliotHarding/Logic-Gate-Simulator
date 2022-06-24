#ifndef GATEFPGA_H
#define GATEFPGA_H

#include <QDialog>
#include "gate.h"

class GateFPGA : public Gate
{
public:
    GateFPGA(const int& x = 0, const int& y = 0);
    GateFPGA(std::vector<Node*>& inputNodesToCopy, std::vector<Node*>& outputNodesToCopy, const int& x = 0, const int& y = 0);
    ~GateFPGA();

    ///Gate class functions
    virtual void draw(QPainter& painter) override;
    virtual GameObject* checkClicked(const QPoint& mouse) override;
    virtual void UpdateOutput() override;
    virtual void SaveData(std::ofstream& storage) override;
    virtual Gate* Clone() override;

    ///Position functions
    virtual void offsetPosition(const int& dX, const int& dY) override;
    virtual void setPosition(const int& x, const int& y) override;

    ///FPGA specific functions
    void OpenEditor();
    void setInputs(const uint& numInputs);
    void setOutputs(const uint& numOutputs);

protected:

    void updateEditButtonGeometry();

    void eraseNodeFromAllNodes(Node* pNode);

    QRect m_editButtonRect;

    ///Nodes
    std::vector<Node*> m_inputNodes;
    std::vector<Node*> m_outputNodes;
};

#endif // GATEFPGA_H

#ifndef GATEFPGA_H
#define GATEFPGA_H

#define GateFpgaWidth 100
#define GateFpgaHeight 100
#define BorderWidth 10

#include "gate.h"

class GateFPGA : public Gate
{
public:
    GateFPGA();
    ~GateFPGA();

    virtual void UpdateGraphics(QPainter* painter) override;
    virtual void SetPosition(int x, int y) override;
    virtual bool UpdateClicked(int clickX, int clickY);
    virtual void UpdateOutput() override;
    virtual Gate* Clone() override;

protected:

    const int INPUT_NODES_X = -5;
    const int OUTPUT_NODES_X = GateFpgaWidth + 5;
    const int NODES_Y_DIFF = 10;

    std::vector<Node> m_inputNodes;
    std::vector<Node> m_outputNodes;
};

#endif // GATEFPGA_H

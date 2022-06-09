#include "GateSingleOutput.h"

namespace Settings
{
///Dimensions
const uint GateSingleOutputWidth = 34;
const uint GateSingleOutputHeight = 34;

///Node positions
const uint NodeOffsetX = GateSingleOutputWidth/2;
const uint NodeOffsetY = GateSingleOutputHeight/2;

///Graphics
const uint BorderSize = 7;
const uint ButtonsSize = 20;
const uint GateSize = 10;
const QRect DrawLayoutIn(BorderSize, BorderSize, GateSingleOutputWidth-BorderSize*2, GateSingleOutputHeight-BorderSize*2);
const QRect DrawLayout(0, 0, GateSingleOutputWidth, GateSingleOutputHeight);
const QColor ActiveColor = Qt::red;
const QColor InActiveColor = Qt::lightGray;
}

GateSingleOutput::GateSingleOutput(const uint& x, const uint& y, const GateType& type, const id& nodeId, QWidget* pParent) :
    Gate::Gate(pParent, type, x, y, Settings::GateSingleOutputWidth, Settings::GateSingleOutputHeight),
    m_pOutput(new Node(this, Settings::NodeOffsetX, Settings::NodeOffsetY, OutputNode, nodeId))
{
    m_nodes.push_back(m_pOutput);
}

void GateSingleOutput::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    //Draw gate
    painter.setPen(QPen(Qt::lightGray, Settings::GateSize));
    painter.drawRect(Settings::DrawLayoutIn);

    //Draw active/inactive buttons
    painter.setPen(QPen(m_pOutput->value() ? Settings::ActiveColor : Settings::InActiveColor, Settings::ButtonsSize));
    painter.drawRect(Settings::DrawLayout);
}

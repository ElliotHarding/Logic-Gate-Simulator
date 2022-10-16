#include "GateSingleOutput.h"

namespace Settings
{
///Dimensions
const uint GateSingleOutputWidth = 34;
const uint GateSingleOutputHeight = 34;

///Node positions
const uint NodeOffsetX = 0;
const uint NodeOffsetY = 0;

///Graphics
const uint BorderSize = 7;
const uint ButtonsSize = 20;
const uint GateSize = 10;
const QRect DrawLayoutIn(BorderSize, BorderSize, GateSingleOutputWidth-BorderSize*2, GateSingleOutputHeight-BorderSize*2);
const QRect DrawLayout(0, 0, GateSingleOutputWidth, GateSingleOutputHeight);
const QColor ActiveColor = Qt::red;
const QColor InActiveColor = Qt::lightGray;
const QColor GateColor = Qt::lightGray;
}

GateSingleOutput::GateSingleOutput(const int& x, const int& y, const GateType& type, const id& nodeId) :
    Gate::Gate(type, x, y, Settings::GateSingleOutputWidth, Settings::GateSingleOutputHeight),
    m_pOutput(new Node(this, Settings::NodeOffsetX, Settings::NodeOffsetY, OutputNode, nodeId))
{
    m_nodes.push_back(m_pOutput);
}

void GateSingleOutput::draw(QPainter& painter)
{
    //Draw gate
    painter.setPen(QPen(Settings::GateColor, Settings::GateSize));
    painter.drawRect(Settings::DrawLayoutIn.translated(position().x(), position().y()));

    //Draw active/inactive buttons
    painter.setPen(QPen(m_pOutput->value() ? Settings::ActiveColor : Settings::InActiveColor, Settings::ButtonsSize));
    painter.drawRect(Settings::DrawLayout.translated(position().x(), position().y()));

    drawNodes(painter);
}

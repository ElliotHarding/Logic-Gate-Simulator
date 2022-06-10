#include "GateToggle.h"

namespace Settings
{
///Functionality
const uint MaxToggleFrequencyMs = 2;

///Text
const QFont DisplayFont = QFont("Helvetica", 7);
const QColor DisplayTextColor = Qt::black;
}

GateToggle::GateToggle(const int& x, const int& y, const id& out) :
    GateSingleOutput::GateSingleOutput(x, y, GATE_EMMITTER, out)
{
    m_toggleStateTimer.start(Settings::MaxToggleFrequencyMs);
}

void GateToggle::UpdateOutput()
{
    //done in ToggleOutputState & checkClicked
}

void GateToggle::ToggleOutputState()
{
    m_toggleStateTimer.stop();
    m_toggleStateTimer.start(Settings::MaxToggleFrequencyMs);
    m_pOutput->setValue(!m_pOutput->value());
}

bool GateToggle::checkClicked(const int& x, const int& y)
{
    bool isClicked = GameObject::checkClicked(x, y);

    //If being clicked & toggleStateTimer has finished
    //Then toggle output value of gate
    if (isClicked && m_toggleStateTimer.remainingTime() == 0)
    {
        ToggleOutputState();

        //Todo : 1 notify parent to redraw...
    }

    return isClicked;
}

void GateToggle::draw(QPainter& painter)
{
    GateSingleOutput::draw(painter);

    painter.setPen(QPen(Settings::DisplayTextColor, 1));
    painter.setFont(Settings::DisplayFont);

    //Todo : calcualte pos correctly
    painter.drawText(m_geometry.x() - 7,
                      m_geometry.y() - 10,
                      m_pOutput->value() ? "On" : "Off");
}

Gate *GateToggle::Clone()
{
    GateToggle* clone = new GateToggle(m_geometry.x(), m_geometry.y(), m_pOutput->id());

    //Clone nodes - Todo : not actaully cloning....
    clone->m_pOutput = m_pOutput;

    return clone;
}

void GateToggle::SaveData(std::ofstream &storage)
{
    //Add general gate info
    Gate::SaveGeneralData(storage);

    //Add node information
    m_pOutput->SaveData(storage);

    storage << END_SAVE_TAG_GATE << std::endl;
}


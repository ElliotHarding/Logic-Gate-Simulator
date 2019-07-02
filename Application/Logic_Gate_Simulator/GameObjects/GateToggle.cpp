#include "GateToggle.h"

GateToggle::GateToggle(id out) :
    GateSingleOutput::GateSingleOutput(GATE_EMMITTER, out),
    m_font("Helvetica", 5)
{
    m_toggleStateTimer.start(c_toggleFrequency);
}

void GateToggle::UpdateOutput()
{
    //done in ToggleOutputState & UpdateClicked
}

void GateToggle::ToggleOutputState()
{
    m_toggleStateTimer.stop();
    m_toggleStateTimer.start(c_toggleFrequency);
    m_output.SetValue(!m_output.GetValue());
}

bool GateToggle::UpdateClicked(int clickX, int clickY)
{
    bool isClicked = GameObject::UpdateClicked(clickX,clickY);

    //If being clicked & toggleStateTimer has finished
    //Then toggle output value of gate
    if (isClicked && m_toggleStateTimer.remainingTime() == 0)
    {
        ToggleOutputState();

        QPainter p;
        UpdateGraphics(&p);
    }

    return isClicked;
}

void GateToggle::UpdateGraphics(QPainter *painter)
{
    GateSingleOutput::UpdateGraphics(painter);

    const QPoint pos = GetPosition();

    painter->setPen(QPen(Qt::black, 1));
    painter->setFont(m_font);

    painter->drawText(pos.x() - GateSingleOutputWidth/2,
                      pos.y() - int(GateSingleOutputHeight/3.5),
                      m_output.GetValue() ? "On" : "Off");
}

Gate *GateToggle::Clone()
{
    GateToggle* clone = new GateToggle();

    //Clone position
    QPoint pos = GetPosition();
    clone->SetPosition(pos.x(), pos.y());

    //Clone nodes
    clone->m_output = m_output;

    return clone;
}

void GateToggle::SaveData(std::ofstream &storage)
{
    //Add general gate info
    Gate::SaveGeneralData(storage);

    //todo save states

    //Add node information
    m_output.SaveData(storage);

    storage << END_SAVE_TAG_GATE << std::endl;
}


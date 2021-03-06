#include <QInputDialog>
#include <QWidget>
#include <QString>
#include <QDir>
#include <iostream>
#include <string>

#include "GateTimer.h"
#include "gatefield.h"

GateTimer::GateTimer(id out) :
    GateSingleOutput::GateSingleOutput(GATE_TIMER, out),
    m_font("Helvetica", 5),
    m_remaningTime(m_frequency)
{
    m_output.SetValue(0);
}

void GateTimer::UpdateOutput()
{
    //None, check CheckTimer functionality (Called by parent gatefield)
}

void GateTimer::SaveData(std::ofstream &storage)
{
    //Add general gate info
    Gate::SaveGeneralData(storage);

    storage << std::to_string(m_frequency);

    //Add node information
    m_output.SaveData(storage);

    storage << END_SAVE_TAG_GATE << std::endl;
}

void GateTimer::UpdateGraphics(QPainter *painter)
{
    GateSingleOutput::UpdateGraphics(painter);

    const QPoint pos = GetPosition();
    const std::string frequency = std::to_string(m_frequency) + "Mhz";

    painter->setFont(m_font);
    painter->drawText(pos.x() - GateSingleOutputWidth/3, pos.y() - (GateSingleOutputHeight/4), QString::fromStdString(frequency));
}

Gate *GateTimer::Clone()
{
    GateTimer* clone = new GateTimer();

    //Clone position
    QPoint pos = GetPosition();
    clone->SetPosition(pos.x(), pos.y());

    //Clone nodes
    clone->m_output = m_output;

    clone->m_frequency = m_frequency;

    return clone;
}

bool GateTimer::CheckTimer()
{
    //If timer timed out, reset & switch output
    if(m_remaningTime-- < 1)
    {
        m_remaningTime = m_frequency;
        m_output.SetValue(!m_output.GetValue());
        return true;
    }
    return false;
}


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
    m_font("Helvetica", 5)
{
    m_output.SetValue(0);
    m_timer.start();
}

void GateTimer::UpdateOutput()
{
    //If timer timed out, reset & switch output
    if(m_timer.remainingTime() == 0)
    {
        m_timer.stop();
        m_timer.start(m_frequency);
        m_output.SetValue(!m_output.GetValue());

        //Call to redraw
        ParentField->update();
    }
}

void GateTimer::SaveData(std::ofstream &storage)
{
    //Add general gate info
    Gate::SaveGeneralData(storage);

    //todo add m_frequency
    //....

    //Add node information
    m_output.SaveData(storage);

    storage << END_SAVE_TAG_GATE << std::endl;
}

void GateTimer::UpdateGraphics(QPainter *painter)
{
    UpdateOutput();

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


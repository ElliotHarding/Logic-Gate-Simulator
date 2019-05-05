#include "GateTimer.h"
#include <QInputDialog>
#include <QWidget>
#include <QString>
#include <QDir>
#include <iostream>
#include <string>

GateTimer::GateTimer() :
    GateSingleOutput::GateSingleOutput(GATE_RECIEVER)
{
    m_output.value = 0;
    m_timer.start();
}

void GateTimer::UpdateOutput()
{
    //If timer timed out, reset & switch output
    if(m_timer.remainingTime() == 0)
    {
        m_timer.stop();
        m_timer.start(m_frequency);
        m_output.value = !m_output.value;
    }
}

void GateTimer::SaveData(std::ofstream &storage)
{
    //Add general gate info
    Gate::SaveData(storage);

    //todo add m_frequency
    //....

    //Add node information
    m_output.SaveData(storage);

    storage << END_SAVE_TAG_GATE << std::endl;
}


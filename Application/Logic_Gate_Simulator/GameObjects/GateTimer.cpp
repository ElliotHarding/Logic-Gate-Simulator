#include <QInputDialog>
#include <QWidget>
#include <QString>
#include <QDir>
#include <iostream>
#include <string>

#include "GateTimer.h"
#include "gatefield.h"

GateTimer::GateTimer(const int& x, const int& y, const id& out) :
    GateSingleOutput::GateSingleOutput(x, y, GATE_TIMER, out)
{
    m_timer.setTimerType(Qt::PreciseTimer);
    QObject::connect(&m_timer, SIGNAL(timeout()), this, SLOT(onTick()));

    setFrequency(1000);
}

GateTimer::~GateTimer()
{
    m_timer.stop();
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
    m_pOutput->SaveData(storage);

    storage << END_SAVE_TAG_GATE << std::endl;
}

Gate *GateTimer::Clone()
{
    GateTimer* clone = new GateTimer(m_geometry.x(), m_geometry.y(), m_pOutput->id());
    clone->m_frequency = m_frequency;

    //Clones without the linded nodes... linking comes later.
    clone->m_pOutput->setValue(m_pOutput->value());

    return clone;
}

void GateTimer::setFrequency(int frequency)
{
    m_frequency = frequency;
    m_timer.stop();
    m_timer.setInterval(m_frequency);
    m_timer.start();
}

void GateTimer::onTick()
{
    m_pOutput->setValue(!m_pOutput->value());
}

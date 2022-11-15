#include <QInputDialog>
#include <QWidget>
#include <QString>
#include <QDir>
#include <iostream>
#include <string>

#include "GateTimer.h"
#include "gatefield.h"

GateTimer::GateTimer(const int& x, const int& y, const id& out, const uint& frequency) :
    GateSingleOutput::GateSingleOutput(x, y, GATE_TIMER, out)
{
    m_timer.setTimerType(Qt::PreciseTimer);
    QObject::connect(&m_timer, SIGNAL(timeout()), this, SLOT(onTick()));

    setFrequency(frequency);
}

GateTimer::~GateTimer()
{
    m_timer.stop();
}

void GateTimer::updateOutput()
{
    //None, check CheckTimer functionality (Called by parent gatefield)
}

void GateTimer::saveData(QDomDocument& storage, QDomElement& parentElement)
{
    QDomElement gateElement = storage.createElement(Settings::GateElement);

    Gate::saveGeneralData(storage, gateElement);

    gateElement.setAttribute(Settings::GateTimerFrequencyTag, QString::number(m_frequency));

    m_pOutput->saveData(storage, gateElement);

    parentElement.appendChild(gateElement);
}

Gate *GateTimer::clone()
{
    GateTimer* clone = new GateTimer(position().x(), position().y(), m_pOutput->id());
    clone->m_frequency = m_frequency;
    Gate::baseClone(clone);

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

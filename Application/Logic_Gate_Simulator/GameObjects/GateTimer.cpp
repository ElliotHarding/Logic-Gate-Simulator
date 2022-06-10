#include <QInputDialog>
#include <QWidget>
#include <QString>
#include <QDir>
#include <iostream>
#include <string>

#include "GateTimer.h"
#include "gatefield.h"

namespace Settings
{
const QFont TimerFont = QFont("Helvetica", 5);
const QFontMetrics TimerFontMetrics(TimerFont);
}

GateTimer::GateTimer(const int& x, const int& y, const id& out) :
    GateSingleOutput::GateSingleOutput(x, y, GATE_TIMER, out)
{
    m_pTimer = new QTimer();
    m_pTimer->setTimerType(Qt::PreciseTimer);
    QObject::connect(m_pTimer, SIGNAL(timeout()), this, SLOT(onTick()));
    m_pTimer->start(m_frequency);
}

GateTimer::~GateTimer()
{
    m_pTimer->stop();
    delete m_pTimer;
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

void GateTimer::draw(QPainter& painter)
{
    GateSingleOutput::draw(painter);

    painter.setFont(Settings::TimerFont);
    painter.drawText(position().x(), position().y() - (Settings::TimerFontMetrics.height()/4), QString::number(m_frequency) + "Mhz");
}

Gate *GateTimer::Clone()
{
    GateTimer* clone = new GateTimer(m_geometry.x(), m_geometry.y(), m_pOutput->id());

    //Clone nodes
    clone->m_pOutput = m_pOutput; //Todo : not actually cloning

    clone->m_frequency = m_frequency;

    return clone;
}

void GateTimer::setFrequency(int frequency)
{
    m_frequency = frequency;
    m_pTimer->stop();
    m_pTimer->start(m_frequency);
}

void GateTimer::onTick()
{
    m_pOutput->setValue(!m_pOutput->value());
    m_pParentField->update();
}


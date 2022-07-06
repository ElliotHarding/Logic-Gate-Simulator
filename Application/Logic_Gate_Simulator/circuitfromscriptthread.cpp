#include "circuitfromscriptthread.h"

//////////////////////////////////////////////////////////////////////////
/// \brief CircuitFromScriptThread::CircuitFromScriptThread
///
CircuitFromScriptThread::CircuitFromScriptThread() : QThread()
{
}

void CircuitFromScriptThread::setup(const uint& numInputs, const uint& numOutputs, const QString& script, const int& maxSeconds, const uint& percentageRandomGate, const uint& maxGates)
{
    m_numInputs = numInputs;
    m_numOutputs = numOutputs;
    m_script = script;
    m_maxSeconds = maxSeconds;
    m_percentageRandomGate = percentageRandomGate;
    m_maxGates = maxGates;
}

void CircuitFromScriptThread::run()
{
    //emit circuitGenSuccess();
    emit circuitGenFailure("");
}

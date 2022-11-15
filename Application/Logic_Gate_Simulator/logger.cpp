#include "logger.h"
#include <string>
#include <QDebug> //Qt only

std::ofstream Logger::m_logFile;
LogLevel Logger::m_logLevelFilter;
bool Logger::m_bFailed;

bool Logger::init(std::string logFilePath, const LogLevel logLevelFilter)
{
    m_logLevelFilter = logLevelFilter;

    m_logFile.open(logFilePath, std::ios_base::app);

    m_bFailed = m_logFile.fail();

    return !m_bFailed;
}

void Logger::log(const LogLevel logLevel, const std::string logEntry)
{
    if(!m_bFailed && logLevel >= m_logLevelFilter)
    {
        m_logFile << std::to_string(logLevel) << " : " << logEntry << std::endl;
    }

    //Qt only
    qDebug() << QString::number(logLevel) + " : " + QString::fromStdString(logEntry);
}

void Logger::setLogLevelFilter(const LogLevel logLevel)
{
    m_logLevelFilter = logLevel;
}

bool Logger::setFilePath(const std::string filePath)
{
    if(!m_bFailed)
    {
        m_logFile.close();
    }

    m_logFile.open(filePath, std::ios_base::app);

    m_bFailed = m_logFile.fail();

    return !m_bFailed;
}

Logger::Logger()
{
}

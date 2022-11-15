#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>

enum LogLevel
{
    LL_Info = 0,
    LL_Warn = 1,
    LL_Error = 2,
    LL_Fatal = 3
};

namespace Settings
{
const std::string LogFilePath = "debuglog.txt";
const LogLevel LogLevel = LL_Info;
}

class Logger
{
public:       
    static bool init(std::string logFilePath = Settings::LogFilePath, const LogLevel logLevel = Settings::LogLevel);
    static void log(const LogLevel logLevel, const std::string logEntry);

    static void setLogLevelFilter(const LogLevel logLevel);
    static bool setFilePath(const std::string filePath);

private:
    Logger();

    static std::ofstream m_logFile;
    static LogLevel m_logLevelFilter;
    static bool m_bFailed;
};

#endif // LOGGER_H

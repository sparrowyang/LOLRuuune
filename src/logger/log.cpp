#include "log.h"
using time_point = std::chrono::system_clock::time_point;

Logger::Logger(){}
Logger::Logger(std::string logname, std::string logfile)
{
    m_logName = logname;
    fopen_s(&m_logFile, logfile.c_str(), "a");
    if (!m_logFile)
    {
        exit(555);
    }
}
std::string Logger::serializeTimePoint()
{
    std::time_t tt = std::chrono::system_clock::to_time_t(m_time);
    std::tm tm = *std::localtime(&tt); // GMT (UTC)
    // std::tm tm = *std::localtime(&tt); //Locale time-zone, usually UTC by default.
    std::stringstream ss;
    ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}
void Logger::log(LogType type, std::string text)
{
    m_time = std::chrono::system_clock::now();
    std::string s_time = serializeTimePoint();
    fprintf(m_logFile, "[%s %s]: %s\n", s_time.c_str(), m_logName.c_str(), text.c_str());
}
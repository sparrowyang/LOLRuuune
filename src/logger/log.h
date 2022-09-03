#pragma once
#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
enum class LogType {
    _INFO,
    _WARM,
    _ERROR
};
class Logger {
public:
    Logger();
    Logger(std::string logname, std::string logfile = "test.log");
    std::string serializeTimePoint();
    void log(LogType type, std::string text);

private:
    std::string m_logName;
    std::string m_logFileName;
    std::chrono::system_clock::time_point m_time;
    FILE* m_logFile;
};
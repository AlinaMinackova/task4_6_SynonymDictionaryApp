#include "pch.h"
#include "pch.h"
#include "Logger.h"

#include <chrono>
#include <iomanip>
#include <sstream>

CLogger& CLogger::Instance()
{
    static CLogger instance;
    return instance;
}

void CLogger::Initialize(const std::string& filename)
{
    m_logFile.open(filename, std::ios::app);
}

void CLogger::Log(LogLevel level, const std::string& message)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_logFile.is_open())
    {
        m_logFile << GetCurrentTime()
            << " | "
            << LevelToString(level)
            << " | "
            << message
            << std::endl;
    }
}

std::string CLogger::GetCurrentTime() const
{
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);

    std::tm localTime{};
    localtime_s(&localTime, &time);

    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");

    return oss.str();
}

std::string CLogger::LevelToString(LogLevel level) const
{
    switch (level)
    {
    case LogLevel::Info: return "INFO";
    case LogLevel::Warning: return "WARNING";
    case LogLevel::Error: return "ERROR";
    default: return "UNKNOWN";
    }
}

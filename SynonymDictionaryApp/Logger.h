#pragma once

#include <string>
#include <fstream>
#include <mutex>

enum class LogLevel
{
    Info,
    Warning,
    Error
};

class CLogger
{
public:
    static CLogger& Instance();

    void Initialize(const std::string& filename);
    void Log(LogLevel level, const std::string& message);

private:
    CLogger() = default;
    std::ofstream m_logFile;
    std::mutex m_mutex;

    std::string GetCurrentTime() const;
    std::string LevelToString(LogLevel level) const;
};


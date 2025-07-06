#pragma once

#include <string>

constexpr uint32_t DEFAULT_BUFFER_CAPACITY = 1024;
constexpr uint32_t BUFFER_SOFT_CAP = 0.75f * DEFAULT_BUFFER_CAPACITY;

constexpr char DEBUG_PREPEND[]{"[DEBUG]: "};
constexpr char INFO_PREPEND[]{"\x1B[32m[INFO]: \033[0m"};
constexpr char WARN_PREPEND[]{"\x1B[93m[WARN]: \033[0m"};
constexpr char ERROR_PREPEND[]{"\x1B[33m[ERROR]: \033[0m"};

enum class ErrorLevel
{
    DEBUG,
    INFO,
    WARN,
    ERROR
};

class HogLog
{
public:
    HogLog(HogLog& aOther) = delete;

    static HogLog& GetInstance();

    static void Log(ErrorLevel aErrLevel, char* apLogString);
    static void Log(ErrorLevel aErrLevel, std::string aLogString);
    static void Logf(ErrorLevel aErrLevel, char* apLogString, ...);
    static void Logf(ErrorLevel aErrLevel, std::string aLogString, ...);
    static void LogNow(ErrorLevel aErrLevel, char* apLogString);
    static void LogNow(ErrorLevel aErrLevel, std::string aLogString);
    static void LogNow(ErrorLevel aErrLevel, const char* aLogString);
    static void LogfNow(ErrorLevel aErrLevel, char* apLogString, ...);
    static void LogfNow(ErrorLevel aErrLevel, std::string aLogString, ...);

    static void SetImmediateLogging(bool aImmediateLogging);
    static void SetBufferCapacity(uint32_t aNewCapacity);

private:
    HogLog() = default;
    ~HogLog() = default;
    static std::string StringifyErrorLevel(ErrorLevel aErrLevel);
    void Append(char* apInput);
    void Append(std::string aInput);
    bool ShouldFlush();
    void Flush();

    std::string m_logBuffer;
    uint32_t m_bufferCapacity = DEFAULT_BUFFER_CAPACITY;
    uint32_t m_bufferSoftCap = BUFFER_SOFT_CAP;
    bool m_immediateLogging = false;
};

#include "HogLog.h"
#include "HogStringUtils.h"
#include <cstdarg>
#include <cstdio>
#include <utility>

HogLog& HogLog::GetInstance()
{
    static HogLog logger;
    return logger;
}

void HogLog::Log(ErrorLevel aErrLevel, char* apLogString)
{
    std::string out(apLogString);
    Log(aErrLevel, out);
}

void HogLog::Log(ErrorLevel aErrLevel, std::string aLogString)
{
    std::string out = StringifyErrorLevel(aErrLevel);
    out.append(aLogString);
    HogLog& logger = GetInstance();
    logger.Append(out);
}

void HogLog::Logf(ErrorLevel aErrLevel, char* apString, ...)
{
    std::string out(apString);
    va_list args;
    va_start(args, apString);
    Logf(aErrLevel, out, args);
    va_end(args);
}

void HogLog::Logf(ErrorLevel aErrLevel, std::string aLogString, ...)
{
    std::string out = StringifyErrorLevel(aErrLevel);
    va_list args;
    va_start(args, aLogString);
    HogStringUtils::Format(aLogString, args);
    va_end(args);
    HogLog& logger = GetInstance();
    logger.Append(out);
}

void HogLog::LogNow(ErrorLevel aErrLevel, char* apLogString)
{
    std::string out(apLogString);
    LogNow(aErrLevel, out);
}

void HogLog::LogNow(ErrorLevel aErrLevel, std::string aLogString)
{
    std::string out = StringifyErrorLevel(aErrLevel);
    out.append(aLogString);
    std::printf("%s", out.c_str());
}

void HogLog::LogfNow(ErrorLevel aErrLevel, char* apLogString, ...)
{
    std::string out = StringifyErrorLevel(aErrLevel);
    va_list args;
    va_start(args, apLogString);
    HogStringUtils::Format(apLogString, args);
    va_end(args);
    out.append(apLogString);
    std::printf("%s", out.c_str());
}

void HogLog::LogfNow(ErrorLevel aErrLevel, std::string aLogString, ...)
{
    std::string out = StringifyErrorLevel(aErrLevel);
    va_list args;
    va_start(args, aLogString);
    HogStringUtils::Format(aLogString, args);
    va_end(args);
    std::printf("%s", out.c_str());
}

void HogLog::SetImmediateLogging(bool aImmediateLogging)
{
    HogLog& logger = GetInstance();
    logger.m_immediateLogging = aImmediateLogging;
}

void HogLog::SetBufferCapacity(uint32_t aNewCapacity)
{
    HogLog& logger = GetInstance();
    logger.m_bufferCapacity = aNewCapacity;
    logger.m_bufferSoftCap = logger.m_bufferCapacity * 0.75f;
}

std::string HogLog::StringifyErrorLevel(ErrorLevel aErrLevel)
{
    std::string ret;
    switch(aErrLevel)
    {
        case ErrorLevel::DEBUG:
            ret.append(DEBUG_PREPEND);
            break;
        case ErrorLevel::INFO:
            ret.append(INFO_PREPEND);
            break;
        case ErrorLevel::WARN:
            ret.append(WARN_PREPEND);
            break;
        case ErrorLevel::ERROR:
            ret.append(ERROR_PREPEND);
            break;
        default:
            std::unreachable();
    }
    return ret;
}

void HogLog::Append(char* apInput)
{
    std::string appending(apInput);
    Append(appending);
}

void HogLog::Append(std::string aInput)
{
    if(ShouldFlush())
    {
        Flush();
    }

    if(m_immediateLogging)
    {
        std::printf("%s", aInput.c_str());
        return;
    }

    m_logBuffer.append(aInput);
    if(!m_logBuffer.ends_with('\n'))
    {
        m_logBuffer += '\n';
    }
}

bool HogLog::ShouldFlush()
{
    return m_logBuffer.size() >= BUFFER_SOFT_CAP;
}

void HogLog::Flush()
{
    std::printf("%s", m_logBuffer.c_str());
    m_logBuffer.clear();
}

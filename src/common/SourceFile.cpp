#include "common/HogDefine.h"
#include "common/HogString.h"
#include "common/SourceFile.h"

#include <filesystem>
#if !IS_POSIX && !IS_WINDOWS
#include <exception>
#endif

SourceFile::SourceFile(const char8_t* apPath)
{
    std::filesystem::path filePath(apPath);
    if(std::filesystem::exists(filePath))
    {
        m_filePath = HogString(apPath);
    }
    else 
    {
        m_filePath = HogString();
    }
}

SourceFile::SourceFile(const char* apPath)
{
    const char8_t* pPath = reinterpret_cast<const char8_t*>(apPath);
    std::filesystem::path filePath(apPath);
    if(std::filesystem::exists(filePath))
    {
        m_filePath = HogString(apPath);
    }
    else 
    {
        m_filePath = HogString();
    }
}

SourceFile::SourceFile(SourceFile& aOther)
{
    m_filePath = aOther.m_filePath.Clone();
}

HogString SourceFile::ToHogString()
{
    return HogString(m_filePath);
}


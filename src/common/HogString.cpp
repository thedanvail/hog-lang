#include "HogString.h"
#include "HogStringUtils.h"

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <string>

HogString::HogString()
{
    SetReservedSize(DEFAULT_BUFF_SIZE);
}

HogString::~HogString()
{
    delete[] m_pBuffer;
}

HogString::HogString(char aChar)
{
    SetReservedSize(1);
    m_pBuffer[0] = aChar;
}

HogString::HogString(const char* apString, std::size_t aBuffSize)
{
    InitBuff(apString, aBuffSize);
}

HogString::HogString(const HogString& aOther)
{
    SetReservedSize(aOther.Size());
    std::char_traits<char>::copy(m_pBuffer, aOther.Str(), aOther.Size() - 1);
}

HogString::HogString(const HogString&& aOther)
{
    SetReservedSize(aOther.Size());
    m_pBuffer = std::move(aOther.m_pBuffer);
}

HogString::HogString(const uint32_t aSize)
{
    SetReservedSize(aSize);
}

HogString::HogString(const std::size_t aSize)
{
    SetReservedSize(aSize);
}

HogString& HogString::operator=(const HogString& aOther)
{
    if(this == &aOther)
    {
        return *this;
    }
    HogString tmp(aOther);
    char* temp = m_pBuffer;
    m_pBuffer = const_cast<char*>(aOther.Str());

    return *this;
}

bool HogString::operator==(const HogString& aOther) const
{
    if(m_size == aOther.m_size)
    {
        return std::char_traits<char>::compare(m_pBuffer, aOther.m_pBuffer, m_size);
    }
    return false;
}

void HogString::InitBuff(const char* apString, std::size_t aBuffSize)
{
    const char* ch8 = reinterpret_cast<const char*>(apString);
    InitBuff(ch8, aBuffSize);
}

void HogString::SetLargerBuffSize(uint32_t aSize)
{
    if(aSize <= Size())
    {
        return;
    }
    char* newBuff = static_cast<char*>(std::malloc(aSize * sizeof(char)));
    std::memcpy(newBuff, m_pBuffer, m_size);
    delete[] m_pBuffer;
    m_pBuffer = newBuff;
    m_size = aSize;
}

void HogString::SetSmallerBuffSize(uint32_t aSize)
{
    if(aSize > Size())
    {
        SetLargerBuffSize(aSize);
    }
    char* newBuff = static_cast<char*>(std::malloc(aSize * sizeof(char)));
    std::memcpy(newBuff, m_pBuffer, aSize);
    delete[] m_pBuffer;
    m_pBuffer = newBuff;
    m_size = aSize;
}

void HogString::SetReservedSize(uint32_t aSize)
{
    if(aSize == m_size)
    {
        return;
    }

    if(aSize < m_size)
    {
        SetSmallerBuffSize(aSize);
    }

    else
    {
        SetLargerBuffSize(aSize);
    }
}

void HogString::Sprintf(const char* aBaseString, ...)
{
    if(m_size == 0)
    {
        SetReservedSize(DEFAULT_BUFF_SIZE);
    }
    std::va_list args;
    va_start(args, aBaseString);

    const char* baseString = reinterpret_cast<const char*>(aBaseString);
    char* buff = reinterpret_cast<char*>(m_pBuffer);
    VarArgPrintf(buff, Size(), baseString, args);

    va_end(args);
}

void HogString::Append(HogString aAppending)
{
    Append(aAppending.Str());    
}

void HogString::Append(char* aAppending)
{
    if(!aAppending)
    {
        return;
    }
    std::size_t appendSize = std::char_traits<char>::length(aAppending);
    std::size_t oldSize = Size();
    char* offset = m_pBuffer + oldSize;
    SetReservedSize(Size() + appendSize);
    std::char_traits<char>::copy(offset, aAppending, appendSize-1);
}

void HogString::VarArgPrintf(char* apString, uint32_t aDestSize, const char* apFormatBuffer, va_list aArgs)
{
#ifdef IS_POSIX
    vsnprintf(apString, aDestSize, apFormatBuffer, aArgs);
#elif IS_WINDOWS
    _vsnprintf_s(apString, aDestSize, apFormatBuffer, aArgs);
#endif
}

HogString HogString::Clone()
{
    std::size_t newSize = Size();
    char* newBuff = new char[Size()];
    std::memcpy(newBuff, m_pBuffer, newSize);
    return HogString(newBuff, newSize);
}

void HogString::ToUpper()
{
    HogStringUtils::ToUpper(m_pBuffer);
}

char* HogString::QueueToChar8Array(std::queue<char>& q) const {
    if (q.empty()) {
        return nullptr;
    }

    std::vector<char> buffer;
    while (!q.empty()) {
        buffer.push_back(q.front());
        q.pop(); 
    }

    buffer.push_back('\0');
    char* result = new char[buffer.size()];
    std::copy(buffer.begin(), buffer.end(), result);
    return result;
}

#include "HogString.h"
#include "StringUtils.h"

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

HogString::HogString(char8_t aChar)
{
    SetReservedSize(1);
    m_pBuffer[0] = aChar;
}

HogString::HogString(const char8_t* apString, std::size_t aBuffSize)
{
    InitBuff(apString, aBuffSize);
}

HogString::HogString(const char* apString, std::size_t aBuffSize)
{
    InitBuff(apString, aBuffSize);
}

HogString::HogString(const HogString& aOther)
{
    SetReservedSize(aOther.Size());
    std::char_traits<char8_t>::copy(m_pBuffer, aOther.Str(), aOther.Size() - 1);
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
    char8_t* temp = m_pBuffer;
    m_pBuffer = const_cast<char8_t*>(aOther.Str());

    return *this;
}

bool HogString::operator==(const HogString& aOther) const
{
    if(m_size == aOther.m_size)
    {
        return std::char_traits<char8_t>::compare(m_pBuffer, aOther.m_pBuffer, m_size);
    }
    return false;
}

void HogString::InitBuff(const char* apString, std::size_t aBuffSize)
{
    const char8_t* ch8 = reinterpret_cast<const char8_t*>(apString);
    InitBuff(ch8, aBuffSize);
}

void HogString::InitBuff(const char8_t* apString, std::size_t aBuffSize)
{
    if(!aBuffSize)
    {
        aBuffSize = std::char_traits<char8_t>::length(apString);
    }
    m_pBuffer = new char8_t[aBuffSize];
    std::char_traits<char8_t>::copy(m_pBuffer, apString, aBuffSize-1);
}

void HogString::SetLargerBuffSize(uint32_t aSize)
{
    if(aSize <= Size())
    {
        return;
    }
    char8_t* newBuff = static_cast<char8_t*>(std::malloc(aSize * sizeof(char8_t)));
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
    char8_t* newBuff = static_cast<char8_t*>(std::malloc(aSize * sizeof(char8_t)));
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

void HogString::Sprintf(const char8_t* aBaseString, ...)
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

void HogString::Append(char8_t* aAppending)
{
    if(!aAppending)
    {
        return;
    }
    std::size_t appendSize = std::char_traits<char8_t>::length(aAppending);
    std::size_t oldSize = Size();
    char8_t* offset = m_pBuffer + oldSize;
    SetReservedSize(Size() + appendSize);
    std::char_traits<char8_t>::copy(offset, aAppending, appendSize-1);
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
    char8_t* newBuff = new char8_t[Size()];
    std::memcpy(newBuff, m_pBuffer, newSize);
    return HogString(newBuff, newSize);
}

void HogString::ToUpper()
{
    HogStringUtils::ToUpper(m_pBuffer);
}

char8_t* HogString::QueueToChar8Array(std::queue<char8_t>& q) const {
    if (q.empty()) {
        return nullptr;
    }

    std::vector<char8_t> buffer;
    while (!q.empty()) {
        buffer.push_back(q.front());
        q.pop(); 
    }

    buffer.push_back('\0');
    char8_t* result = new char8_t[buffer.size()];
    std::copy(buffer.begin(), buffer.end(), result);
    return result;
}

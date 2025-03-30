#pragma once

#include "HogArray.h"

#include <cstdarg>
#include <cstdint>

constexpr uint32_t DEFAULT_BUFF_SIZE = 256;

// A better way of dealing with UTF-8 characters.
class HogString
{
public:
    HogString();
    ~HogString();
    HogString(const char* apString, std::size_t aBuffSize = 0);
    HogString(const char8_t* apString, std::size_t aBuffSize = 0);
    HogString(char8_t aChar);
    HogString(const HogString& aOther);
    HogString(const HogString&& aOther);
    HogString(const uint32_t aSize);
    HogString(const std::size_t aSize);
    HogString& operator=(const HogString& aOther);
    bool operator==(const HogString& aOther) const;

    void Append(char8_t* aAppending);
    void Append(HogString aAppending);
    void Sprintf(const char8_t* aBaseString, ...);
    void Sprintf(HogString aBaseString, ...);
    void SprintfAppend(char8_t* aBaseString, ...);
    void SprintfAppend(HogString aBaseString, ...);
    void InitBuff(uint32_t aSize);
    void SetReservedSize(uint32_t aRequestedSize);
    std::size_t Size() const { return m_size; }
    const char8_t* Str() const { return m_pBuffer; }
    char8_t* ToOwnedStr();
    void ToUpper();
    void ToLower();
    void Clear();
    void Reset();
    HogString Clone();
    HogArray<char8_t*> Split(const char c) const;
    HogArray<char8_t*> Split(const char* c) const;
    HogArray<char8_t*> Split(const char8_t c) const;
    HogArray<char8_t*> Split(const char8_t* c) const;

private:
    void InitBuff(const char8_t* apString, std::size_t aBuffSize = 0);
    void InitBuff(const char* apString, std::size_t aBuffSize = 0);
    void VarArgPrintf(char* apString, uint32_t aDestSize, const char* apFormatBuffer, va_list aArgs);
    void SetLargerBuffSize(uint32_t aSize);
    void SetSmallerBuffSize(uint32_t aSize);

    // TODO: move this to a StringUtils namespace that I plan to (won't) eventually make.
    HogArray<char8_t*> _Split(char8_t* string, const char8_t* delimiter) const;
    uint32_t m_size;
    char8_t* m_pBuffer;
};

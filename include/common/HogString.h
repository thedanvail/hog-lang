#pragma once

#include <cstdarg>
#include <cstdint>
#include <queue>

constexpr uint32_t DEFAULT_BUFF_SIZE = 256;

// A better way of dealing with UTF-8 characters.
class HogString
{
public:
    HogString();
    ~HogString();
    HogString(const char* apString, std::size_t aBuffSize = 0);
    HogString(char aChar);
    HogString(const HogString& aOther);
    HogString(const HogString&& aOther);
    HogString(const uint32_t aSize);
    HogString(const std::size_t aSize);
    HogString& operator=(const HogString& aOther);
    bool operator==(const HogString& aOther) const;

    void Append(char* aAppending);
    void Append(HogString aAppending);
    void Sprintf(const char* aBaseString, ...);
    void Sprintf(HogString aBaseString, ...);
    void SprintfAppend(char* aBaseString, ...);
    void SprintfAppend(HogString aBaseString, ...);
    void InitBuff(uint32_t aSize);
    void SetReservedSize(uint32_t aRequestedSize);
    std::size_t Size() const { return m_size; }
    const char* Str() const { return m_pBuffer; }
    char* ToOwnedStr();
    void ToUpper();
    void ToLower();
    void Clear();
    void Reset();
    HogString Clone();

private:
    char* QueueToChar8Array(std::queue<char>& q) const;
    void InitBuff(const char* apString, std::size_t aBuffSize = 0);
    void VarArgPrintf(char* apString, uint32_t aDestSize, const char* apFormatBuffer, va_list aArgs);
    void SetLargerBuffSize(uint32_t aSize);
    void SetSmallerBuffSize(uint32_t aSize);

    // TODO: move this to a StringUtils namespace that I plan to (won't) eventually make.
    uint32_t m_size;
    char* m_pBuffer;
};

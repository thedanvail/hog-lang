#include <cstdarg>
#include <cstdint>

class HogString
{
public:
    HogString() = default;
    HogString(char8_t);
    HogString(char8_t*);
    ~HogString();

    void Sprintf(char8_t* aBaseString, ...);
    void Append(char8_t* aAppending);
    void SprintfAppend(char8_t* aBaseString, ...);
    uint32_t Size();
    void Clear();
    void Reset();

private:

    void VarArgPrintf(char8_t* aString, uint32_t aDestSize, const char8_t* apFormatBuffer, va_list aArgs);
    char8_t m_buffer[];
};

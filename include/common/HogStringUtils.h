#pragma once

#include <string>
#include <vector>

template <typename Function>
concept CallableReturnChar = requires(Function f, char c) 
{
    { f(c) } -> std::convertible_to<char>;
};


namespace HogStringUtils
{
    template<CallableReturnChar T>
    inline void ApplyFuncToString(char* apString, T aFunction);

    void ReplaceChar(char* apBaseString, const char aCharToReplace, const char aNewChar);
    void ReplaceChar(char* apBaseString, const std::vector<char> aCharToReplace, const char aNewChar);
    void Format(char* apString, ...);
    void Format(std::string apString, ...);
    void VarArgPrintf(char* apString, uint32_t aDestSize, const char* apFormatBuffer, va_list aArgs);
    char ToUpperChar(char aChar);
    char ToLowerChar(char aChar);
    void ToUpper(char* apString);
    void ToLower(char* apString);
    std::string Trim(std::string aInput);
    std::vector<std::string> SplitString(char* apString, char aDelimiter);
    std::vector<std::string> SplitString(std::string aString, char aDelimiter);
    bool IsOnlyWhitespace(std::string aString);
    bool IsOnlyWhitespace(char* apString);
}

template<CallableReturnChar T>
inline void HogStringUtils::ApplyFuncToString(char *apString, T aFunction)
{
    if(!apString)
    {
        return;
    }

    std::size_t strLen = std::char_traits<char>::length(apString);

    for(int i = 0; apString[i] != '\0' && i < strLen; ++i)
    {
        apString[i] = aFunction(apString[i]);
    }
}

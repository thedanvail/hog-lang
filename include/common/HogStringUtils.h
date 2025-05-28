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

    // This is less efficient than just changing the input string,
    // but it's safer if we don't mutate the input.
    // Fuck you functional bros.
    std::string Trim(const std::string aInput);
    std::vector<std::string> SplitString(const std::string aString, char aDelimiter);
    std::vector<std::string> SplitString(const std::string aString, const std::string aDelimiter);
    std::vector<std::string> SplitString(char* apString, char aDelimiter);
    bool IsOnlyWhitespace(std::string aString);
    bool IsOnlyWhitespace(char* apString);
    bool StringsEqual(std::string aFirstStr, std::string aSecondStr);
    bool StringContainsAny(const std::string& aInput, std::vector<std::string> aContains);
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

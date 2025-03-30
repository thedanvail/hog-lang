#pragma once

#include <functional>
namespace HogStringUtils
{
    void ReplaceChar(char8_t* apBaseString, const char8_t aCharToReplace, const char8_t aNewChar);
    void ReplaceChar(char* apBaseString, const char aCharToReplace, const char aNewChar);
    void ApplyFuncToString(const char8_t* apString, std::function<char(unsigned char)> aFunction);
    void ToUpper(char* apString);
    void ToUpper(char8_t* apString);
    void ToLower(char* apString);
    void ToLower(char8_t* apString);
}

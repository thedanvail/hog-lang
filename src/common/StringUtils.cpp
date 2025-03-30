#include "common/StringUtils.h"
#include <cctype>

namespace HogStringUtils {
    void ReplaceChar(char8_t* apBaseString, const char8_t aCharToReplace, const char8_t aNewChar)
    {
        if(!apBaseString)
        {
            return;
        }

        for(int i = 0; apBaseString[i] != '\0'; ++i)
        {
            if(apBaseString[i] != aCharToReplace)
            {
                continue;
            }

            apBaseString[i] = aNewChar;
        }
    }

    void ReplaceChar(char* apBaseString, const char aCharToReplace, const char aNewChar)
    {
        char8_t* pBaseString  = reinterpret_cast<char8_t*>(apBaseString);
        char8_t charToReplace = static_cast<char8_t>(aCharToReplace);
        char8_t newChar       = static_cast<char8_t>(aNewChar);
        
        ReplaceChar(pBaseString, charToReplace, newChar);
    }

    void ApplyFuncToString(char8_t* apString, std::function<char(unsigned char)> aFunction)
    {
        if(!apString)
        {
            return;
        }

        for(int i = 0; apString[i] != '\0'; ++i)
        {
            apString[i] = aFunction(apString[i]);
        }
    }

    void ToUpper(char8_t* apString)
    {
        ApplyFuncToString(apString, std::toupper);
    }

    void ToUpper(char* apString)
    {
        ToUpper(reinterpret_cast<char8_t*>(apString));
    }

    void ToLower(char8_t* apString)
    {
        ApplyFuncToString(apString, std::tolower);
    }

    void ToLower(char* apString)
    {
        ToLower(reinterpret_cast<char8_t*>(apString));
    }

}

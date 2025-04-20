#include "HogDefine.h"
#include "HogStringUtils.h"
#include <cctype>
#include <cstdarg>
#include <cstdio>
#include <string>
#include <vector>

namespace HogStringUtils {
    void ReplaceChar(char* apBaseString, const char aCharToReplace, const char aNewChar)
    {
        if(!apBaseString)
        {
            return;
        }
        std::size_t strLen = std::char_traits<char>::length(apBaseString);

        for(int i = 0; apBaseString[i] != '\0' && i < strLen; ++i)
        {
            if(apBaseString[i] == aCharToReplace)
            {
                apBaseString[i] = aNewChar;
            }
        }
    }

    void Format(char* apString, ...)
    {
        if(!apString)
        {
            return;
        }
        std::size_t neededLength = std::char_traits<char>::length(apString);
        va_list args;
        va_start(args, apString);
        int32_t requiredSize = vsnprintf(nullptr, 0, apString, args);
        char* ret = new char[requiredSize];
        VarArgPrintf(ret, requiredSize, apString, args);
        va_end(args);
        delete[] apString;
        apString = ret;
    }

    void Format(std::string aString, ...)
    {
        char* pInputString = const_cast<char*>(aString.c_str());
        va_list args;
        va_start(args, aString);
        Format(pInputString, args);
        va_end(args);
        aString = std::string(pInputString);
    }

    void VarArgPrintf(char* apString, uint32_t aDestSize, const char* apFormatBuffer, va_list aArgs)
    {
#ifdef IS_POSIX
        vsnprintf(apString, aDestSize, apFormatBuffer, aArgs);
#elif IS_WINDOWS
        _vsnprintf_s(apString, aDestSize, apFormatBuffer, aArgs);
#endif
    }

    char ToUpperChar(char aChar)
    {
        return static_cast<char>(std::toupper(static_cast<unsigned char>(aChar)));
    }

    char ToLowerChar(char aChar)
    {
        return static_cast<char>(std::tolower(static_cast<unsigned char>(aChar)));
    }

    void ToUpper(char* apString)
    {
        ApplyFuncToString(apString, ToUpperChar);
    }

    void ToLower(char* apString)
    {
        ApplyFuncToString(apString, ToLowerChar);
    }

    std::vector<std::string> SplitString(std::string aString, char aDelimiter)
    {
        std::vector<std::string> result;
        if(!aString.size())
        {
            return result; 
        }
        std::string tmp;
        for(char c : aString)
        {
            if(c == aDelimiter)
            {
                result.push_back(tmp);
                tmp.clear();
            }
            else 
            {
                tmp += c;
            }
        }
        result.push_back(tmp);
        return result;
    }
    
    std::vector<std::string> SplitString(char* apString, char aDelimiter)
    {
        if(!apString)
        {
            return std::vector<std::string>();
        }
        std::string str(apString);
        return SplitString(str, aDelimiter);
    }
}

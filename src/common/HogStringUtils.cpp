#include "HogDefine.h"
#include "HogStringUtils.h"

#include <algorithm>
#include <cctype>
#include <cstdarg>
#include <cstdio>
#include <string>
#include <vector>

namespace HogStringUtils {
    void ReplaceChar(char* apBaseString, const char aCharToReplace, const char aNewChar)
    {
        ENSURE_PTR(apBaseString);
        std::size_t strLen = std::char_traits<char>::length(apBaseString);

        for(std::size_t i = 0; apBaseString[i] != '\0' && i < strLen; ++i)
        {
            if(apBaseString[i] == aCharToReplace)
            {
                apBaseString[i] = aNewChar;
            }
        }
    }

    void ReplaceChar(char* apBaseString, const std::vector<char> aCharsToReplace, const char aNewChar)
    {
        ENSURE_PTR(apBaseString);
        std::size_t strLen = std::char_traits<char>::length(apBaseString);

        for(std::size_t i = 0; apBaseString[i] != '\0' && i < strLen; ++i)
        {
            for(char c : aCharsToReplace)
            {
                if(c == apBaseString[i])
                {
                    apBaseString[i] = aNewChar;
                }
            }
        }
    }

    void Format(char* apString, ...)
    {
        ENSURE_PTR(apString);
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

    [[nodiscard]] std::string Trim(const std::string aInput)
    {
        if(aInput.empty())
        {
            return aInput;
        }

        auto start = std::find_if_not(aInput.begin(), aInput.end(), [](unsigned char ch) {
                return std::isspace(ch);
                });
        auto end = std::find_if_not(aInput.rbegin(), aInput.rend(), [](unsigned char ch) {
                return std::isspace(ch);
                }).base();
        if (start >= end) {
            return "";
        }
        return std::string(start, end);
    }

    void TrimInplace(std::string &aInput)
    {
        RETURN_IF_EMPTY(aInput);
        for(std::size_t idx = 0; idx < aInput.size(); ++idx)
        {
            if(isspace(aInput.at(idx)))
            {
                aInput.erase(idx, 1);
            }
            // We've reached the end of our whitespace, so exit the loop.
            else 
            {
                break;
            }
        }

        for(auto iter = aInput.rbegin(); iter != aInput.rend(); ++iter)
        {
            if(!isspace(*iter))
            {
                aInput.erase(iter.base(), aInput.end());
            }
        }
    }

    std::vector<std::string> SplitString(const std::string& aString, char aDelimiter)
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


    std::vector<std::string> SplitString(const std::string& aString, const std::string aDelimiter)
    {
        std::size_t delimiterLength = aDelimiter.size();
        std::vector<std::string> result;
        if(!delimiterLength)
        {
            return result;
        }
        
        std::size_t splitBeginIdx = 0;
        for(std::size_t idx = 0; idx < aString.size(); ++idx)
        {
            if(aString[idx] == aDelimiter[0] && idx + delimiterLength < aString.size())
            {
                std::string substr = aString.substr(idx, delimiterLength);
                if(substr == aDelimiter)
                {
                    result.emplace_back(aString.substr(splitBeginIdx, idx - splitBeginIdx));
                    splitBeginIdx = idx + delimiterLength;
                    idx += delimiterLength - 1;  // -1 because loop will ++idx
                }
            }
        }

        result.emplace_back(aString.substr(splitBeginIdx));
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

    bool IsOnlyWhitespace(std::string aString)
    {
        for(char c : aString)
        {
            if(!std::isspace(c))
            {
                return false;
            }
        }
        return true;
    }

    bool IsOnlyWhitespace(char* apString)
    {
        ENSURE_PTR_RETURN_VAL(apString, false);
        std::size_t strLen = std::char_traits<char>::length(apString);
        for(std::size_t i = 0; apString[i] != '\0' && i < strLen; ++i)
        {
            if(!std::isspace(apString[i]))
            {
                return false;
            }
        }
        return true;
    }

    bool StringsEqual(std::string aFirstStr, std::string aSecondStr)
    {
        if(aFirstStr.size() != aSecondStr.size())
        {
            return false;
        }
        for(uint32_t idx = 0; idx < aFirstStr.size(); ++idx)
        {
            if(aFirstStr[idx] != aSecondStr[idx])
            {
                return false;
            }
        }
        return true;
    }

    bool StringContainsAny(const std::string& aInput, std::vector<std::string> aContains)
    {
        for(std::string& str : aContains)
        {
            if(aInput.contains(str))
            {
                return true;
            }
        }
        return false;
    }
}

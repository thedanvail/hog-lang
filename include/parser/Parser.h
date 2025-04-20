#pragma once

#include "Types.h"

#include <string>
#include <vector>

class ParsedText
{
public:
    ParsedText() = default;
    ~ParsedText() = default;

private:
    std::vector<ParsedText> m_parsedText;
};

class Parser
{
public:
    Parser() = default;
    ~Parser() = default;
    void Parse(std::string aInput);

private:
    std::string GetTextInsideParenthesis(std::string aInput);
};

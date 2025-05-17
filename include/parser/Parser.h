#pragma once

#include "SourceFile.h"
#include "Types.h"

#include <string>
#include <string_view>
#include <vector>

class ParsedText
{
public:
    ParsedText() = default;
    ~ParsedText() = default;

private:
    std::vector<ParsedText> m_parsedText;
};

    /* TODO:
     * So I think I need to group arguments into labels/locations, types, and values.
     * After that, dispatch arguments to various functions and have them transformed into
     * the appropriate types.
     * Down the line, this will need to go from dynamic dispatch and interpretation to 
     * static binary, but writing a linker sounds hard and like a problem for future Dan.
     * A lot of this will need to be hoisted from the parser into another part as this
     * _should_ just be something that makes the syntax tree and not something that is doing
     * all of this execution. Ho hum.
     */
class Parser
{
public:
    Parser() = default;
    ~Parser() = default;
    void Parse(std::string aInput);
    void ParseFile(SourceFile aFile);
    LineType GetLineType(std::string_view aLine);
    HogFuncs DetermineFunction(std::string_view aFunc);
    ArgType DetermineArgType(std::string aArg);
    std::vector<std::string> GetArgsInParens(std::string aInput);
    void ExecuteFunction(HogFuncs aFunc, std::vector<std::string> aArgs);
    void ExecuteFunction(HogFuncs aFunc, std::vector<Arg> aArgs);

private:
    // TODO: std::string GetTextInsideParenthesis(std::string aInput);
    HogFuncs SquealOrHogtie(std::string_view aFunc);
};

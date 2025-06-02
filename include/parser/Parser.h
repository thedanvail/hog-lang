#pragma once

#include "SourceFile.h"
#include "Types.h"

#include <string>
#include <string_view>
#include <vector>

/* TODO:
 * So I think I need to group arguments into labels/locations, types, and values.
 * After that, dispatch arguments to various functions and have them transformed into
 * the appropriate types.
 * Down the line, this will need to go from dynamic dispatch and interpretation to 
 * static binary, but writing a linker sounds hard and like a problem for future Dan.
 * A lot of this will need to be hoisted from the parser into another part as this
 * SHOULD just be something that makes the syntax tree and not something that is doing
 * all of this execution. Ho hum.
 */
class Parser
{
public:
    Parser() = default;
    ~Parser() = default;
    void Parse(std::string aInput);
    void ParseFile(SourceFile aFile);
    void ParseBlock(const std::string_view aInput);
    void ParseLine(const std::string_view aInput);
    LineType GetLineType(std::string aLine);
    HogFuncs DetermineFunction(std::string_view aFunc);
    ArgType DetermineArgType(std::string aArg);
    std::vector<std::string> GetArgsInParens(std::string aInput);
    void ExecuteFunction(HogFuncs aFunc, std::vector<std::string> aArgs);
    void ExecuteFunction(HogFuncs aFunc, std::vector<Arg> aArgs);
    bool IsExpression(const std::string& aInput);
    void Evaluate(const std::string& aInput);

private:
    // TODO: std::string GetTextInsideParenthesis(std::string aInput);
    HogFuncs SquealOrHogtie(std::string_view aFunc);
    bool IsValidNamedSymbol(std::string_view aSymbol) { return true; } // TODO: Not this.
    bool IsValidObjectFunction(std::string_view aSymbol) { return true; } // TODO: Not this.
};

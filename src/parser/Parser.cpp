#include "HogAst.h"
#include "HogBase.h"
#include "HogStd.h"
#include "HogStringUtils.h"
#include "Parser.h"
#include "Symbol.h"
#include "Types.h"
#include <string>

void Parser::ParseFile(SourceFile aFile)
{
    // TODO: This... all of this.
}

void Parser::Parse(std::string aInput)
{
    std::printf("Parsing line: %s\n", aInput.c_str());
    // TODO: Figure out if the line is a function or assignment
    LineType lt = GetLineType(aInput); 
    if(lt == LineType::FUNCTION)
    {
        std::size_t parenIndex = aInput.find('(');
        HogFuncs function = DetermineFunction(aInput.substr(0, parenIndex));
        if(function == HogFuncs::INVALID)
        {
            std::string errMsg("Invalid syntax: \"");
            errMsg.append(aInput);
            errMsg.append("\"");
            CatchFireAndDie(errMsg);
        }
        std::vector<std::string> args = GetArgsInParens(aInput);
        // TODO: Determine the arg type
        ExecuteFunction(function, args);
    }
    if(lt == LineType::ASSIGNMENT)
    {
        std::printf("DAN I GOT AN ASSIGNMENT\n");
        // TODO: Do the assignment. That means we have to start dealing
        // with memory and symbols.
        // I need to know the type that's being assigned so I can fuck
        // with the sizing.
        // NOTE: It's guaranteed (right now) that the current syntax is
        // `hogtie 5 my_var` or something like that, so the second element
        // in the split string should be the value.
        // Maybe everything should be copy by default both for the sake of hogging
        // memory and making the functional bros calm the fuck down.
        std::vector<std::string> splitStr = HogStringUtils::SplitString(aInput, ' ');
        // Remove `;` from the symbol.
        splitStr[2].pop_back();
        HOG_ASSERT(splitStr[0].compare("hogtie") == 0, "You're in an assignment but it's not hogtie, fuck head.");
        // Now we gotta figure out the type of the value being assigned.

        // For the sake of the short term, we're just gonna deal with numbers.
        if(!IsNumeric(splitStr[1]))
        {
            CatchFireAndDie("DAN I FOUND SOMETHING AND ITS NOT A NUMBER WHAT DO");
        }
        HogSymbolTree::AddSymbol(splitStr[2], splitStr[1]);

        // We need to now create a symbol for the variable.

        std::printf("Successfully dealt with an assignment.\n");
    }
}

LineType Parser::GetLineType(std::string aLine)
{
    std::string trimmed = HogStringUtils::Trim(aLine);
    if(!trimmed.size())
    {
        return LineType::EMPTY;
    }
    
    // Comment lines
    if(trimmed.starts_with("//"))
    {
        return LineType::EMPTY;
    }

    // Remove anything that is an inline comment
    if(trimmed.find("//") != std::string::npos)
    {
        trimmed = HogStringUtils::SplitString(trimmed, "//")[0];
    }

    // Actual assignment. Ignore below.
    if(trimmed.starts_with("hogtie"))
    {
        return LineType::ASSIGNMENT;
    }

    if(trimmed.find('('))
    {
        return LineType::FUNCTION;
    }

    // Assignment
    if(trimmed.find('=') != std::string::npos)
    {
        // Check for `!=` and `==`
    }

    return LineType::INVALID;
}

HogFuncs Parser::DetermineFunction(std::string_view aFunc)
{
    std::size_t functionNameLength = aFunc.length();
    switch(functionNameLength)
    {
        case 4:
            return HogFuncs::OINK;
            break;
        case 6:
            if(aFunc.starts_with("hogtie"))
            {
                return HogFuncs::HOGTIE;
            }
            return HogFuncs::SQUEAL;
            break;
    }
    return HogFuncs::INVALID;
}

std::vector<std::string> Parser::GetArgsInParens(std::string aInput)
{
    std::vector<std::string> ret;

    std::size_t firstParenIndex = aInput.find('(') + 1; // Move past the paren
    std::size_t charsToLastParen = aInput.find(')') - firstParenIndex; // We want the length
    if(firstParenIndex == std::string::npos || charsToLastParen == std::string::npos)
    {
        CatchFireAndDie("INVALID SYNTAX, BITCH");
    }
    std::string splittingStr = aInput.substr(firstParenIndex, charsToLastParen);
    ret = HogStringUtils::SplitString(splittingStr, ',');
    for(std::string str : ret)
    {
        std::printf("STR: %s\n", str.c_str());
        if(IsExpression(str))
        {
            Evaluate(str);
        }
    }
    return ret;
}

void Parser::ExecuteFunction(HogFuncs aFunc, std::vector<std::string> aArgs)
{
    char* arg;
    switch(aFunc)
    {
        case HogFuncs::INVALID:
            CatchFireAndDie("How did you do this?");
            break;
        case HogFuncs::OINK:
            std::printf("OINKING\n");
            std::printf("%s\n", aArgs[0].c_str());
            break;
        case HogFuncs::SQUEAL:
            arg = const_cast<char*>(aArgs[0].c_str());
            HogStringUtils::ToUpper(arg);
            std::printf("%s\n", arg);
            break;
        case HogFuncs::HOGTIE:
            std::printf("HOG TYING\n");
            break;
    }
}

ArgType Parser::DetermineArgType(std::string aArg)
{
    ArgType type = ArgType::STRING;
    std::printf("%s\n", aArg.c_str());
    return type;
}

bool Parser::IsExpression(const std::string& aInput)
{
    std::vector<std::string> containing{"+", "-", "*"};
    if(HogStringUtils::StringContainsAny(aInput, containing))
    {
        return true;
    }
    return false;
}

void Parser::Evaluate(const std::string& aInput)
{
    // TODO: Split on operands (+, -, etc) or chaining functions
    // and then evaluate. Fucking recursion.
    // Return Types::Value
}


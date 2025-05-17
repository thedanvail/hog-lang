#include "Parser.h"
#include "HogBase.h"
#include "HogStringUtils.h"

void Parser::ParseFile(SourceFile aFile)
{
    // TODO: This... all of this.
}

void Parser::Parse(std::string aInput)
{
    std::printf("Parsing.\n");
    // TODO: Figure out if the line is a function or assignment
    
    // End new shit
    std::size_t parenIndex = aInput.find('(');
    HogFuncs function = DetermineFunction(aInput.substr(0, parenIndex));
    if(function == HogFuncs::INVALID)
    {
        std::string errMsg("Invalid syntax: ");
        errMsg.append(aInput);
        CatchFireAndDie(errMsg);
    }
    std::vector<std::string> args = GetArgsInParens(aInput);
    // TODO: Determine the arg type
    ExecuteFunction(function, args);
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


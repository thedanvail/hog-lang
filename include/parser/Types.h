#pragma once

#include <cmath>
#include <string>
#include <variant>

enum class HogFuncs
{
    INVALID,
    OINK,
    SQUEAL,
    HOGTIE, // Not a function but fuck you what're you gonna do about it?
};

using ArgValue = std::variant<int64_t, std::float_t, std::string>;
enum class ArgType
{
    INVALID,
    STRING,
    INT,
    FLOAT,
};

enum class LineType
{
    FUNCTION,
    OPERAND,
};

enum class Ops 
{
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    ASSIGNMENT,
    BOOLEAN_EQUAL,
    BOOLEAN_NOT_EQUAL,
    BOOLEAN_AND,
    BOOLEAN_OR,
};

union Label 
{
    std::string str;
    void* addr;
};

struct Arg
{
    ArgType  type;
    ArgValue value;
    Label    label;
};


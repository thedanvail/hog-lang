#pragma once

#include <cmath>
#include <cstdint>
#include <string>
#include <variant>


// TODO: Clean this fucking place up.
enum class HogFuncs
{
    INVALID,
    OINK,
    SQUEAL,
    HOGTIE, // Not a function but fuck you what're you gonna do about it?
};

enum class ValType 
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
    ASSIGNMENT,
    EMPTY,
    INVALID,
};

enum class Ops 
{
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    MODULO,
    ASSIGNMENT,
    BOOLEAN_EQUAL,
    BOOLEAN_NOT_EQUAL,
    BOOLEAN_AND,
    BOOLEAN_OR,
};

using ArgValue = std::variant<int64_t, std::float_t, std::string>;
enum class ArgType
{
    INVALID,
    STRING,
    INT,
    FLOAT,
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

namespace HogTypes
{
    ValType GetType(const std::string& aValue);
    std::variant<std::int64_t, std::string> GetValue(const ValType aType, const std::string& aValue);
}

struct Value
{
    Value() = default;
    Value(const std::string& aVal);
    ValType type;
    std::variant<std::int64_t, std::string> value;
};


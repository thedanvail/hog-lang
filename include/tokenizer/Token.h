#pragma once

#include <vector>

// FIXME: This should only be temporary
using FunctionPtr = void*;

enum class Token
{
    OPCODE, // +, -, /, *, %, etc.
    FUNCTION,
    VARIABLE,
    KEYWORD,
    LINE_COMMENT,
    BLOCK_COMMENT_START,
    BLOCK_COMMENT_END,
    CODE_BLOCK_START,
    CODE_BLOCK_END
};

enum class FunctionType 
{
    OINK,
    SQUEAL,
    UNKNOWN
};

enum class ValueType
{
    STRING,
    NUMBER,
};

struct TypeValuePair
{
    ValueType type;
    void* value;
};

struct FunctionInvocation
{
    FunctionPtr function;
    std::vector<TypeValuePair> args;
};



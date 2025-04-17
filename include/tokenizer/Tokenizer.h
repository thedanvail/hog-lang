#pragma once

#include "HogString.h"

#include <string>
#include <cstdint>

enum class Token
{
    TOKEN_OPCODE,
    TOKEN_FUNCTION,
    TOKEN_VARIABLE,
    TOKEN_KEYWORD
};

enum class OpCode
{
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    NONE
};

struct HogVal
{
    int64_t val;
    OpCode op;
};


struct HogNode
{
    HogVal val;
    HogNode* lhs;
    HogNode* rhs;
};

/// Takes the char and parses it into an operation token.
/// If you want multi-character operations, that's too damn bad.
OpCode ToOpCode(const char ch);

/// Takes the first character in the string and parses it into an operation token.
/// If you want multi-character operations, see the note in the comments above. 
OpCode ToOpCode(const HogString aString);

/// Takes the first character in the string and parses it into an operation token.
/// If you want multi-character operations, see the note in the comments above. 
OpCode ToOpCode(const char* const c);

/// Takes the first character in the string and parses it into an operation token.
/// If you want multi-character operations, see the note in the comments above. 
OpCode ToOpCode(const char8_t* const c);


OpCode ToOpCode(std::string s);

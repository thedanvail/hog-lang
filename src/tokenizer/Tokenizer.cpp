#include "Tokenizer.h"


namespace Tokenizer
{
OpCode ToOpCode(char ch)
{
    OpCode op;
    switch(ch)
    {
        case '+':
            op = OpCode::ADD;
            break;
        case '-':
            op = OpCode::SUBTRACT;
            break;
        case '*':
            op = OpCode::MULTIPLY;
            break;
        case '/':
            op = OpCode::DIVIDE;
            break;
        default:
            op = OpCode::NONE;
    }
    return op;
}

OpCode ToOpCode(std::string s)
{
    return ToOpCode(s.at(0));
}

OpCode ToOpCode(const char* const pChar)
{
    if(pChar)
    {
        return ToOpCode(pChar[0]);
    }
    return OpCode::NONE;
}
} // namespace Tokenizer

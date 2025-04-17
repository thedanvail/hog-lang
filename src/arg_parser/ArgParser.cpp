#include "ArgParser.h"
#include "HogString.h"
#include "Error.h"
#include <cctype>

Arg::Arg(char8_t* feed)
{
    char8_t flag = feed[1];
    flag = std::toupper(flag);
    switch(flag)
    {
        case 'i':
        case 'I':
            m_flag = ArgFlags::I;
            break;
        case 'o':
        case 'O':
            m_flag = ArgFlags::O;
        default:
            HogString errorMsg("Incorrect error flag: ");
            errorMsg.Append(feed[1]);
            HogError::Panic(errorMsg.Str());
    }

    uint8_t idx = 3; // Skip the "-", the letter, and the following space
    while(idx < MAX_CHARS+3 && feed[idx] != '\0')
    {

    }
}

ArgParser::ArgParser(int argc, char8_t* argv[])
{
    for (int i=1; i < argc; ++i)
    {
        Arg arg(argv[i]);
        m_args.push_back(Arg(argv[i]));
    }
}

const std::vector<Arg> ArgParser::Args() const 
{
    return m_args;
}



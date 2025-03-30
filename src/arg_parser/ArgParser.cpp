#include "../../include/arg_parser/ArgParser.h"
#include "../../include/common/HogString.h"
#include "../../include/common/Error.h"

Arg::Arg(char8_t* feed)
{
    switch(feed[1])
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
    uint8_t idx = 3;
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



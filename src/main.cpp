#include "arg_parser/ArgParser.h"
#include "common/HogString.h"

#include <cstdio>
#include <fstream>
#include <utpp/utpp.h>


int main(int argc, char** argv)
{
    std::printf("%d\n", argc);

    for(std::size_t idx = 1; idx < argc; idx++)
    {
        std::printf("%s\n", argv[idx]);
    }

    std::ifstream file(argv[1]);
    char contents[2048];
    file.read(contents, 2048);
    std::printf("%s\n", contents);
    // UnitTest::RunAllTests();
}

#include "ArgParser.h"
#include "Parser.h"

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>

std::string ReadFile(std::string_view path)
{
    std::ifstream stream(path.data());

    if(!stream)
    {
        return std::string();
    }
    
    std::string out;
    std::size_t read_size = 4096;
    std::string buf(read_size, '\0');
    while(stream.read(& buf[0], read_size))
    {
        out.append(buf, 0, stream.gcount());
    }
    out.append(buf, 0, stream.gcount());
    return out;
}

int main(int argc, char** argv)
{
    std::printf("%d\n", argc);

    for(std::size_t idx = 1; idx < argc; idx++)
    {
        std::printf("%s\n", argv[idx]);
    }
    
    std::string path = std::filesystem::current_path();
    path.append("/");
    path.append(argv[1]);
    std::string sourceFile = ReadFile(path);
    std::cout << sourceFile << std::endl;

    std::string delimiter = "\n";
    std::vector<std::string> lines;
    std::string line = sourceFile.substr(0, sourceFile.find(delimiter));
    std::cout << line << std::endl << std::endl;

    Parser p;
    p.Parse(line);
}

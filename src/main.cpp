#include "HogStringUtils.h"
#include "Parser.h"

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>

void PrintHelp()
{
    std::printf("------------------------------------------------\n");
    std::printf("|             Welcome to Hog Lang              |\n");
    std::printf("------------------------------------------------\n");
    std::printf("\n");
    std::printf("We hope you hate your stay.\n");
}

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
    PrintHelp();
    std::string path = std::filesystem::current_path();
    path.append("/");
    path.append(argv[1]);
    std::string sourceFile = ReadFile(path);
    std::cout << sourceFile << std::endl;

    char delimiter = '\n';
    std::vector<std::string> lines = HogStringUtils::SplitString(sourceFile, delimiter);
    Parser p;

    for(std::string line : lines)
    {
        if(!HogStringUtils::IsOnlyWhitespace(line))
        {
            std::cout << "Line in source file: " << line << std::endl << std::endl;
            p.Parse(line);
        }
    }
    std::string line = sourceFile.substr(0, sourceFile.find(delimiter));

}

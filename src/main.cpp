#include "HogLLVM.h"
#include "HogLog.h"
#include "HogStringUtils.h"
#include "Parser.h"

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <llvm-14/llvm/IR/IRBuilder.h>
#include <llvm-14/llvm/IR/Type.h>
#include <string>
#include <unistd.h>

void PrintHelp()
{
    std::printf("\n");
    std::printf("------------------------------------------------\n");
    std::printf("|             Welcome to Hog Lang              |\n");
    std::printf("------------------------------------------------\n");
    std::printf("\n");
    std::printf("          We hope you hate your stay.\n");
    std::printf("\n");
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

    HogLLVM& hogLLVM = HogLLVM::GetInstance();
    // llvm::IRBuilder<>& builder = HogLLVM::GetBuilder();
    // llvm::Type* voidType = builder.getVoidTy();
    // llvm::Type* i32Type = builder.getInt32Ty();
    // std::vector<llvm::Type*> argTypes;
    // argTypes.push_back(i32Type);
    // argTypes.push_back(i32Type);
    // constexpr bool isVariadic = false;
    // llvm::FunctionType* ex = llvm::FunctionType::get(i32Type, argTypes, isVariadic);
    // llvm::Function* exFunc = hogLLVM.CreateFunction(ex, "add");

    // Name the args
    // auto iter = exFunc->arg_begin();
    // llvm::Value* arg1 = &*iter++;
    // arg1->setName("FirstArg");
    // llvm::Value* arg2 = &*iter++;
    // arg2->setName("SecondArg");

    // Create code block
    hogLLVM.AppendMain();
    hogLLVM.PrintIR();
    HogLog::LogNow(ErrorLevel::DEBUG, "Attempting to compile to object file");
    hogLLVM.EmitObject("test.hog.o");
}

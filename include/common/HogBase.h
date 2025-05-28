#pragma once

#include <cstdio>
#include <ctime>
#include <exception>
#include <string>


inline void CatchFireAndDie(std::string errorMsg)
{
    std::printf("\n%s\n", errorMsg.c_str());
    std::terminate();
}

inline void CatchFireAndDie(const char* errorMsg)
{
    std::printf("\n%s\n", errorMsg);
    std::terminate();
}

#define HOG_ASSERT(cond, err) if(!(cond)) CatchFireAndDie(err);

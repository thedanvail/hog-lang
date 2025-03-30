#include "../../include/common/Error.h"

#include <cstdlib>
#include <cstdio>
#include <iostream>

void HogError::Panic(const std::string &errorMessage)
{
    std::cerr << "Ya messed up, dipshit. " << std::endl << errorMessage << std::endl;
    std::abort();
}

void HogError::Panic(const char8_t* errorMsg)
{
    const char* msg = reinterpret_cast<const char*>(errorMsg);
    std::printf("Ya messed up, dipshit.\n%s\n", msg);
    std::abort();

}

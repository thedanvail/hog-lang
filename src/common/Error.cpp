#include "../../include/common/Error.h"

#include <cstdlib>
#include <iostream>

void HogError::Panic(const std::string &errorMessage)
{
    std::cerr << "Ya messed up, dipshit. " << std::endl << errorMessage << std::endl;
    std::abort();
}

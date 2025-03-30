#include <string>

namespace HogError
{
    void Panic(const std::string& errorMessage);
    void Panic(const char8_t* errorMsg);
}

#include <string>


namespace Symbols 
{

    template<typename T>
    struct Symbol 
    {
        T val;
        std::string symbol;
    };
}

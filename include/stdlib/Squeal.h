#include <string>

namespace Squeal
{
    void Squeal(const char* apString);
    void Squeal(const char* apString, ...);
    void Squeal(const std::string& aString);
    void Squeal(const std::string& aString, ...);

    [[nodiscard]] std::string EvalExpr(const std::string aString);
}

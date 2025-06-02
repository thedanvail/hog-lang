#include "HogBase.h"
#include "HogDefine.h"
#include "HogStringUtils.h"
#include <algorithm>
#include "Squeal.h"

void Squeal::Squeal(const char* apString)
{
    ENSURE_PTR(apString);
    std::string input(apString);
    if(input[0] != '"')
    {
        input = EvalExpr(apString);
    }
}

void Squeal::Squeal(const char* apString, ...)
{
    ENSURE_PTR(apString);
    std::string input(apString);
    if(input[0] != '"')
    {
        // If there's no string, we can't evaluate multiple things. So die.
        CatchFireAndDie("You can't evaluate multiple expressions in a print statement, dumbass.");
    }
}

void Squeal::Squeal(const std::string& aString)
{
    RETURN_IF_EMPTY(aString);
}

void Squeal::Squeal(const std::string& aString, ...)
{
    RETURN_IF_EMPTY(aString);
}

[[nodiscard]] std::string Squeal::EvalExpr(const std::string aString)
{
    std::string ret;
    // Alright, let's begin with the ugliest shit you've ever seen.
    // For right now, just basic arithmetic.
    if(aString.contains('+'))
    {
        std::vector<std::string> split = HogStringUtils::SplitString(aString, '+');
        for(std::string& str : split)
        {
            HogStringUtils::TrimInplace(str);
        }
        // Leaving off here. I need to evaluate a simple lhs + rhs
        // knowing that either/both/neither sides could be variables or 
        // constant values.
    }

    return ret;
}

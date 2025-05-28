#include "Types.h"
#include "HogStd.h"
#include <string>

ValType HogTypes::GetType(const std::string &aValue)
{
    if(IsNumeric(aValue))
    {
        return ValType::INT;
    }
    return ValType::INVALID;
}

std::variant<std::int64_t, std::string> HogTypes::GetValue(const ValType aType, const std::string& aValue)
{
    if(IsNumeric(aValue))
    {
        return std::stoi(aValue);
    }

    return aValue;
}

Value::Value(const std::string& aValue)
{
    type = HogTypes::GetType(aValue);
    value = HogTypes::GetValue(type, aValue);
};


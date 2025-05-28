#pragma once

#include "Types.h"
#include <string>
#include <unordered_map>

namespace HogAst
{
    std::size_t Hash(const std::string& s);
}

class HogSymbolTree
{
public:
    HogSymbolTree() = default;
    ~HogSymbolTree() = default;
    HogSymbolTree(HogSymbolTree&) = delete;

    static void AddSymbol(std::string aSymbol, std::string& aVal);

private:
    static HogSymbolTree& GetInstance();
    std::unordered_map<std::size_t, Value> m_map;
};

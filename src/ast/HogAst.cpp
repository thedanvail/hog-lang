#include "HogAst.h"
#include "Types.h"

std::size_t HogAst::Hash(const std::string& s)
{
    return std::hash<std::string>{}(s);
}

HogSymbolTree& HogSymbolTree::GetInstance()
{
    static HogSymbolTree tree;
    return tree;
}

void HogSymbolTree::AddSymbol(std::string aSymbol, std::string& aVal)
{
    HogSymbolTree& tree = GetInstance();
    std::size_t hash = HogAst::Hash(aSymbol);
    struct Value val = Value(aVal);
    tree.m_map[hash] = val;
    std::printf("Added symbol `%s` with value `%s` to the symbol tree.\n", aSymbol.c_str(), aVal.c_str());
}

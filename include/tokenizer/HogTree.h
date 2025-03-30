#pragma once

#include "Tokenizer.h"
class HogTree
{
public:
    HogTree() = default;
    ~HogTree();

private:
    HogNode m_root;
};

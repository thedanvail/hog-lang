#pragma once

#include "HogBase.h"

#include <concepts>

// A simple iterator wrapper class.
// Will work in a similar fashion to the builtin C++ iterator, but better.
// The only constraint is that T must be equality-comparable; that is, it must
// implement its own `operator==(T other)` function to insure this class'
// equality operator behaves as expected.
template<std::equality_comparable T>
class Iterator
{
public:
    Iterator(T* t) : m_index(0) { m_element = t; }
    ~Iterator() = default;
    inline Iterator Begin();
    inline Iterator End();
    inline void Next();
    inline bool operator==(Iterator aOther);
    inline T* Get();

private:
    T* m_element;
    uint32_t m_index;
};


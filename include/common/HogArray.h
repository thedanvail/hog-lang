#pragma once

#include "HogBase.h"
#include <initializer_list>

constexpr uint32_t DEFAULT_ARRAY_SIZE = 32;


template<typename T>
class HogArray
{
public:
    HogArray();
    HogArray(T t);
    HogArray(T t[]);
    HogArray(std::initializer_list<T> list);
    HogArray(HogArray& aOther);
    HogArray(HogArray&& aOther);
    ~HogArray();
    T Pop();
    T Get(uint64_t index) const;
    void Set(T t, uint64_t index);
    void Add(T t);
    void SetSize(uint64_t aNewSize);
    std::size_t Size() const;
    T& operator[](uint64_t index);
    T& operator[](uint64_t index) const;
    void operator=(HogArray aOther);
    bool operator==(const HogArray aOther) const;

private:
    void _Append(T t);
    void _Resize(uint64_t aNewSize = 0);
    std::size_t m_size = DEFAULT_ARRAY_SIZE;
    uint32_t m_lastElement;
    T* m_data;
};

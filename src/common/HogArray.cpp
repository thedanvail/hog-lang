#pragma once

#include "HogArray.h"
#include <cstddef>
#include <cstring>
#include <initializer_list>
#include <iterator>


template<typename T>
HogArray<T>::HogArray()
{
    m_data = new T[m_size];
}

template<typename T>
HogArray<T>::HogArray(T t)
{
    m_data = new T[m_size];
    m_data[0] = t;
}

template<typename T>
HogArray<T>::HogArray(T t[])
{
    constexpr std::size_t arrSize = std::size(t);
    m_data = new T[m_size];
    for(std::size_t i = 0; i < arrSize; ++i)
    {
        m_data[i] = t[i];
    }
}

template<typename T>
HogArray<T>::HogArray(std::initializer_list<T> list)
{
    for(T t : list)
    {
        _Append(t);
    }
}

template<typename T>
HogArray<T>::HogArray(HogArray& aOther)
{
    m_size = aOther.m_size;
    m_lastElement = aOther.m_lastElement;
    std::memcpy(m_data, aOther.m_data, m_size*sizeof(T));
}

template<typename T>
void HogArray<T>::_Resize(uint64_t aNewSize)
{
    if(!aNewSize)
    {
        aNewSize = m_size * 2;
    }

    // TODO: What if we resize to a smaller size?
    T* pOldBuffer = std::move(m_data);
    m_data = new T[aNewSize];
    std::memcpy(m_data, pOldBuffer, m_size);
    m_size = aNewSize;
}

template<typename T>
void HogArray<T>::_Append(T t)
{
    if(m_lastElement + 1 >= m_size)
    {
        _Resize();
    }
    m_lastElement++;
    m_data[m_lastElement] = t;
}

///////////
// Tests //
///////////



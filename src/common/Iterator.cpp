#include "Iterator.h"

#include <cstdint>
#include <stdint.h>

template<std::equality_comparable T>
inline void Iterator<T>::Begin()
{
    if(m_element && m_index)
    {
        m_element -= m_index;
        m_index = 0;
        return this;
    }
}

template<std::equality_comparable T>
inline void Iterator<T>::End()
{
    m_element = nullptr;
    m_index = UINT32_MAX;
}

template<std::equality_comparable T>
inline void Iterator<T>::Next()
{
    if(!m_element)
    {
        m_index = UINT32_MAX;
        return;
    }
    m_element++;
    m_index++;
}

template<std::equality_comparable T>
inline T* Iterator<T>::Get()
{
    return m_element;
}

template<std::equality_comparable T>
inline bool Iterator<T>::operator==(Iterator aOther)
{
    if(!m_element && aOther.m_element)
    {
        return true;
    }

    if(!m_element && aOther.m_element)
    {
        return false;
    }

    if(m_element && !aOther.m_element)
    {
        return false;
    }

    return (*m_element == *aOther.m_element);
}


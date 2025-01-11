#pragma once

class Iterator 
{
public:
    virtual ~Iterator() = default;
    virtual void Next(Iterator& iter) = 0;
    virtual Iterator Begin() = 0;
    virtual Iterator End() = 0;
};


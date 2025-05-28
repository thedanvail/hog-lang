#pragma once

#include "HogBase.h"

/*
 * Okay, so I need to allocate memory for the program.
 * The allocation needs to be 2-5x what the user requests.
 * How exactly do I allocate on the stack vs on the heap?
 * My intuition says `unsigned char` as a byte and then
 * stuff that in an array.
 */

namespace HogMemory
{
    void* Allocate(uint64_t aNumBytes);
}

#pragma once
#include "cpu_types.h"

class memory
{
private:
    byte mem[64 * 1024];

public:
    void store(word address, byte value);
    byte load_byte(word address);
    word load_word_le(word address);
};

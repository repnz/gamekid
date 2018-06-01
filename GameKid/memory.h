#pragma once
#include "cpu_types.h"

class memory
{
private:
    byte mem[64 * 1024];

public:
    
    
    template <typename T>
    T load(word address)
    {
        return *(T*)(mem[address]);
    }

    template <typename T>
    void store(word address, T value)
    {
        *(T*)(mem[address]) = value;
    }

    void store_byte(word address, byte value);
    byte load_byte(word address);
    word load_word_le(word address);
};

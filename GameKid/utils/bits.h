#pragma once
#include "GameKid/cpu_types.h"

namespace bits
{
    template <typename T>
    T set_bit_on(T value, byte place)
    {
        return value | (1 << place);
    }

    template <typename T>
    T set_bit_off(T value, byte place)
    {
        return value & ~(1 << place);
    }

    template <typename T>
    T set_bit(T value, byte place, bool is_on)
    {
        if (is_on) return set_bit_on(value, place);
        return set_bit_off(value, place);
    }

    template <typename T>
    bool check_bit(T value, byte place) 
    {
        return value & (1 << place);
    }
}

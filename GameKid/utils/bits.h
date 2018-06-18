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

    inline bool check_carry_up(word before, word after, byte bit_place)
    {
        const word bits = (1 << bit_place);
        return (before & bits) < (after & bits);
    }

    inline bool check_carry_down(word before, word after, byte bit_place)
    {
        const word bits = (1 << bit_place);
        return (before & bits) > (after & bits);
    }
}

#pragma once
#include "gamekid/utils/types.h"

namespace gamekid::utils::bits {
    template <typename T>
    T set_bit_on(T value, byte place) {
        return value | (1 << place);
    }

    template <typename T>
    T set_bit_off(T value, byte place) {
        return value & ~(1 << place);
    }

    template <typename T>
    T set_bit(T value, byte place, bool is_on) {
        if (is_on) return set_bit_on(value, place);
        return set_bit_off(value, place);
    }

    template <typename T>
    bool check_bit(T value, byte place) {
        return value & (1 << place);
    }

    inline word mask_bits(byte bit_place) {
        return (1 << (bit_place + 1)) - 1;
    }

    inline bool check_carry_up(word before, word after, byte bit_place) {
        const word mask = mask_bits(bit_place);
        return (before & mask) > (after & mask);
    }

    inline bool check_carry_down(word before, word after, byte bit_place) {
        const word mask = mask_bits(bit_place);
        return (before & mask) < (after & mask);
    }
}

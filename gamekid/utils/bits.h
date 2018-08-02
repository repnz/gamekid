#pragma once
#include "gamekid/utils/types.h"
#include <array>

namespace gamekid::utils::bits {
    template <typename T>
    constexpr T set_bit_on(const T value, const byte place) {
        return value | (1 << place);
    }

    template <typename T>
    constexpr T set_bit_off(const T value, const byte place) {
        return value & ~(1 << place);
    }

    template <typename T>
    constexpr T set_bit(const T value, const byte place, const bool is_on) {
        if (is_on) return set_bit_on(value, place);
        return set_bit_off(value, place);
    }

    template <typename T>
    constexpr bool check_bit(const T value, const byte place) {
        return value & (1 << place);
    }

    constexpr word mask_bits(byte bit_place) {
        return (1 << (bit_place + 1)) - 1;
    }

    constexpr bool check_carry_up(const word before, const word after, const byte bit_place) {
        const word mask = mask_bits(bit_place);
        return (before & mask) > (after & mask);
    }

    constexpr bool check_carry_down(const word before, const word after, const byte bit_place) {
        const word mask = mask_bits(bit_place);
        return (before & mask) < (after & mask);
    }
}

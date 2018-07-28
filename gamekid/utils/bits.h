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

    template <int field_size, int array_size>
    class bits_array {
        static_assert(field_size == 1 || field_size == 2 || field_size == 4);
    public:
        static constexpr byte fields_in_byte = 8 / field_size;
        static constexpr byte inner_array_size = array_size / fields_in_byte;
        std::array<byte, inner_array_size> value;
    
        explicit constexpr bits_array(const std::array<byte, inner_array_size>& value) : value(value){}
        constexpr bits_array() {}

        static constexpr byte get_bit_index(byte array_index) {
            return (8 - field_size) - (array_index % fields_in_byte) * field_size;
        }

        constexpr byte get(byte index) const {
            return (value[index / fields_in_byte] >> get_bit_index(index)) & mask_bits(field_size-1);
        }
    };
}

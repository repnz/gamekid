#pragma once
#include <gamekid/utils/types.h>
#include <array>
#include "gamekid/utils/bits.h"

namespace gamekid::video::io {
    struct tile {
        explicit tile(const std::array<byte, 16>& value) : colors(value){}

        // 64 colors
        // each color is 2 bits
        utils::bits::bits_array<2, 64> colors;

        // Index can be value from 0 to 64 (represents the index of the color)
        // the color can be 0 to 3 (the index from the pallete)
        byte  get_color(byte color_index) const {
            return colors.get(color_index);
        }

        byte get_color(byte x, byte y) const {
            return get_color(y * 8 + x);
        }

    };

    static_assert(sizeof(tile) == sizeof(byte[16]));
}

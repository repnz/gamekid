#pragma once
#include <gamekid/utils/types.h>
#include <array>
#include "gamekid/utils/bits.h"
#include "gamekid/utils/bytes.h"

namespace gamekid::video::io {
    struct tile {
        explicit tile(const std::array<byte, 16>& value) : colors(value){}

        // 64 colors
        // each color is 2 bits
        std::array<byte, 16> colors;

        // x and y can be between 0 to 7 (represents the location of the color)
        // the color can be 0 to 3 (the index from the pallete)
        byte get_color(byte x, byte y) const {
            const word row_word = utils::bytes::read_value<word>(&colors[y * 2]);
            const bool b1 = utils::bits::check_bit(row_word, 7 - x);
            const bool b2 = utils::bits::check_bit(row_word, 15 - x);
            const byte res = utils::bits::set_bit(0, 0, b1);
            return utils::bits::set_bit(res, 1, b2);
        }
    };

    static_assert(sizeof(tile) == sizeof(byte[16]));
}

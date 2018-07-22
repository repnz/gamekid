#pragma once
#include <gamekid/utils/types.h>

namespace gamekid::video::io {
    struct tile {
        explicit tile(word value) : value(value){}

        word value;

        // Index can be value from 0 to 7
        // indicates the index of the color to get
        // the color can be 0 to 3 (the index from the pallete)
        byte get_color(byte index) const {
            return (value >> (14 - index * 2)) & 0b11;
        }

        byte get_color(byte x, byte y) const {
            return get_color(y * 8 + x);
        }
    };
}
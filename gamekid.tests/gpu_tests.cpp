#include "pch.h"
#include "gamekid/io/video/tile.h"

namespace gamekid::tests {
    

    TEST(GPU, TILE_GET_COLOR) {
        video::io::tile t(0xCCCC);
        ASSERT_EQ(0b11, t.get_color(0));
        ASSERT_EQ(0b00, t.get_color(1));
        ASSERT_EQ(0b11, t.get_color(2));
    }

    TEST(GPU, TILE_CAST_SAME_WORD) {
        static_assert(sizeof(video::io::tile) == sizeof(word));
        word value = 0x1234;
        auto tile = reinterpret_cast<video::io::tile*>(&value);
        ASSERT_EQ(0x1234, tile->value);
    }

}

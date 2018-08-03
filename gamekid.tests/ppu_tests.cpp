#include "pch.h"
#include "gamekid/io/video/tile.h"

namespace gamekid::tests {
    
    TEST(PPU, TILE_GET_COLOR) {
        std::array<byte, 16> arr = { 0x7A, 0xA7, 0x8B, 0x9C};

        video::io::tile t(arr);

        ASSERT_EQ(0b10, t.get_color(0, 0));
        ASSERT_EQ(0b00, t.get_color(1, 1));
        ASSERT_EQ(0b11, t.get_color(0, 1));
    }
   
}

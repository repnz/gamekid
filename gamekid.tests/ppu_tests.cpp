#include "pch.h"
#include "gamekid/io/video/tile.h"

namespace gamekid::tests {
    

    TEST(PPU, TILE_GET_COLOR) {
        byte value[16];
        value[0] = 0xCC;
        value[1] = 0xCC;
        
        auto t = reinterpret_cast<video::io::tile*>(&value[0]);

        ASSERT_EQ(0b11, t->get_color(0));
        ASSERT_EQ(0b00, t->get_color(1));
        ASSERT_EQ(0b11, t->get_color(2));
    }
}

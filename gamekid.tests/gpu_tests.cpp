#include "pch.h"
#include "gamekid/io/video/tile.h"

namespace gamekid::tests {
    

    TEST(GPU, TILE_GET_COLOR) {
        video::io::tile t(0xCCCC);
        ASSERT_EQ(0b11, t.get_color(0));
        ASSERT_EQ(0b00, t.get_color(1));
        ASSERT_EQ(0b11, t.get_color(2));
    }


}

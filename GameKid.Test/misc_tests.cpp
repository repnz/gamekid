#include "pch.h"
#include <GameKid/cpu.h>

TEST(MISC, SWAP)
{
    cpu c;

    byte val = 0b00001111;
    c.swap(&val);
    ASSERT_EQ(val, 0b11110000);
    ASSERT_EQ(c.F.zero(), false);

    val = 0b10100101;
    c.swap(&val);
    ASSERT_EQ(val, 0b01011010);
    ASSERT_EQ(c.F.zero(), false);

    val = 0;
    c.swap(&val);
    ASSERT_EQ(c.F.zero(), true);
}
#include "pch.h"
#include <GameKid/cpu.h>

TEST(Commands, BIT)
{
    cpu c;

    // 1 bit 0 => zero_flag = 0
    byte val = 0b00000001;
    c.bit(val, 0);
    ASSERT_EQ(c.F.zero(), false);

    // 1 bit 1 => zero_flag = 1
    val = 0b00000001;
    c.bit(val, 1);
    ASSERT_EQ(c.F.zero(), true);
}

TEST(Commands, SET)
{
    cpu c;

    // 0 set 3 => 0b00000100 => 4
    byte val = 0b00000000;
    c.set(&val, 2);
    ASSERT_EQ(val, 4);
}


TEST(Commands, RES)
{
    cpu c;

    // 6 res 3 == 2
    byte val = 0b00000110;
    c.res(&val, 2);
    ASSERT_EQ(val, 2);
}

TEST(Commands, SWAP)
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
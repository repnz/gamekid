#include "pch.h"
#include <GameKid/cpu.h>

TEST(Commands, ADC)
{
    cpu c;

    byte val = 10;
    c.F.carry(true);
    c.adc(&val, 1);

    // 10 + carry_flag + 1 = 12

    ASSERT_EQ(val, 12);
}

TEST(Commands, RL)
{
    cpu c;

    // 128 rl = 1
    byte val = 1 << 7;
    c.rl(&val);
    ASSERT_EQ(val, 1);
    ASSERT_EQ(c.F.carry(), true);

    // 1 rl = 2
    val = 1;
    c.rl(&val);
    ASSERT_EQ(val, 2);
    ASSERT_EQ(c.F.carry(), false);
}

TEST(Commands, RLC)
{
    cpu c;

    // 128 rlc (carry = 0) = 0
    byte val = 1 << 7;
    c.rlc(&val);
    ASSERT_EQ(val, 0);
    ASSERT_EQ(c.F.carry(), true);

    // 1 rlc (carry = 1) = 3
    c.F.carry(true);
    val = 1;
    c.rlc(&val);
    ASSERT_EQ(val, 3);
    ASSERT_EQ(c.F.carry(), false);
}


TEST(Commands, RR)
{
    cpu c;

    // 1 rr == 128
    byte val = 1;
    c.rr(&val);
    ASSERT_EQ(val, 128);
    ASSERT_EQ(c.F.carry(), true);

    // 128 rr == 64
    val = 128;
    c.F.carry(true);
    c.rr(&val);
    ASSERT_EQ(val, 64);
    ASSERT_EQ(c.F.carry(), false);
}

TEST(Commands, RRC)
{
    cpu c;

    // 1 rrc (carry = 0) == 0
    byte val = 1;
    c.rrc(&val);
    ASSERT_EQ(val, 0);
    ASSERT_EQ(c.F.carry(), true);

    // 128 rrc (carry = 1) = 192
    c.F.carry(true);
    val = 128;
    c.rrc(&val);
    ASSERT_EQ(val, 192);
    ASSERT_EQ(c.F.carry(), false);
}

TEST(Commands, SLA)
{
    cpu c;

    // 128 sla == 0
    byte val = 0b10000000;
    c.sla(&val);
    ASSERT_EQ(val, 0);
    ASSERT_EQ(c.F.carry(), true);

    // 64 sla == 128
    val = 0b01000000;
    c.sla(&val);
    ASSERT_EQ(val, 128);
    ASSERT_EQ(c.F.carry(), false);
}

TEST(Commands, SRA)
{
    cpu c;

    // 1 sra == 0
    byte val = 0b00000001;
    c.sra(&val);
    ASSERT_EQ(val, 0);
    ASSERT_EQ(c.F.carry(), true);

    // -128 sra == -64
    val = 0b10000000; // -128
    c.sra(&val);
    ASSERT_EQ(val, 0b11000000); // -64
    ASSERT_EQ(c.F.carry(), false);
}

TEST(Commands, SRL)
{
    cpu c;

    // 1 srl == 0
    byte val = 0b00000001;
    c.sra(&val);
    ASSERT_EQ(val, 0);
    ASSERT_EQ(c.F.carry(), true);

    // 128 srl == 64
    val = 0b10000000;
    c.srl(&val);
    ASSERT_EQ(val, 0b01000000);
    ASSERT_EQ(c.F.carry(), false);
}

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

TEST(Commands, ADD)
{
    cpu c;

    byte val = 10;
    c.add(&val, 2);
    ASSERT_EQ(val, 12);

    val = 255;
    c.add(&val, 1);
    ASSERT_EQ(val, 0);
    ASSERT_EQ(c.F.carry(), true);

    val = 0b00001111;
    c.add(&val, 1);
    ASSERT_EQ(val, 16);
    ASSERT_EQ(c.F.half_carry(), true);
}

TEST(Commands, SUB)
{
    cpu c;

    byte val = 10;
    c.sub(&val, 2);
    ASSERT_EQ(val, 8);

    val = 0;
    c.sub(&val, 1);
    ASSERT_EQ(val, 255);
    ASSERT_EQ(c.F.carry(), true);

    val = 0b00010000;
    c.sub(&val, 1);
    ASSERT_EQ(val, 15);
    ASSERT_EQ(c.F.half_carry(), true);
}

TEST(Commands, SBC)
{
    cpu c;
    
    c.F.carry(true);
    byte val = 10;
    c.sbc(&val, 2);
    ASSERT_EQ(val, 7);
}


TEST(Commands, AND)
{
    cpu c;
    byte val = 0b1010;

    c.and_n(&val, 0b0101);

    ASSERT_EQ(val, 0);
    ASSERT_EQ(c.F.zero(), true);
}

TEST(Commands, OR)
{
    cpu c;
    byte val = 0b1010;

    c.or_n(&val, 0b0101);

    ASSERT_EQ(val, 0b1111);
    ASSERT_EQ(c.F.zero(), false);
}

TEST(Commands, XOR)
{
    cpu c;
    byte val = 0b1110;

    c.xor_n(&val, 0b1101);

    ASSERT_EQ(val, 0b0011);
    ASSERT_EQ(c.F.zero(), false);
}

TEST(Commands, CP)
{
    cpu c;

    byte val = 10;
    c.cp(val, 10);
    ASSERT_EQ(c.F.zero(), true);

    val = 0;
    c.cp(val, 1);
    ASSERT_EQ(c.F.carry(), true);

    val = 100;
    c.cp(val, 50);
    ASSERT_EQ(c.F.zero(), false);
    ASSERT_EQ(c.F.carry(), false);
}


TEST(Commands, INC)
{
    cpu c;

    byte val = 10;
    c.inc(&val);
    ASSERT_EQ(val, 11);
    ASSERT_EQ(c.F.zero(), false);

    val = 0b1111;
    c.inc(&val);
    ASSERT_EQ(c.F.half_carry(), true);

    val = 255;
    c.inc(&val);
    ASSERT_EQ(c.F.zero(), true);;
}

TEST(Commands, DEC)
{
    cpu c;

    byte val = 10;
    c.dec(&val);
    ASSERT_EQ(val, 9);
    ASSERT_EQ(c.F.zero(), false);

    val = 0b00011111;
    c.dec(&val);
    ASSERT_EQ(c.F.half_carry(), true);

    val = 1;
    c.dec(&val);
    ASSERT_EQ(c.F.zero(), true);
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
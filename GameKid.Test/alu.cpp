#include "pch.h"
#include "GameKid/cpu.h"
#include "GameKid/cpu/instruction_set.h"
#include "test_operand.h"

TEST(ALU, ADD_NORMAL)
{
    cpu c;
    test_operand<byte> test_operand(10);
    alu::add_operation(c, test_operand);
    ASSERT_EQ(c.A.load(), 10);
}

TEST (ALU, ADD_CARRY_ON)
{
    cpu c;
    test_operand<byte> test_operand(255);
    alu::add_operation(c, test_operand);
    ASSERT_EQ(c.A.load(), 0);
    ASSERT_EQ(c.F.carry(), true);
}

TEST(ALU, ADD_HALF_CARRY_ON)
{
    cpu c;
    test_operand<byte> test_operand(0b00001111);
    alu::add_operation(c, test_operand);
    ASSERT_EQ(c.A.load(), 16);
    ASSERT_EQ(c.F.half_carry(), true);
}

TEST(ALU, ADC_CARRY_TRUE)
{
    cpu c;
    c.F.carry(true);
    test_operand<byte> test_operand(10);
    alu::adc_operation(c, test_operand);

    // 10 + carry_flag + 1 = 12
    ASSERT_EQ(c.A.load(), 12);
}

TEST(ALU, ADC_CARRY_FALSE)
{
    cpu c;
    c.F.carry(false);
    test_operand<byte> test_operand(10);
    alu::adc_operation(c, test_operand);

    // 10 + 1 = 12
    ASSERT_EQ(c.A.load(), 11);
}

TEST(ALU, SUB_NORMAL)
{
    cpu c;
    test_operand<byte> test_operand(10);
    c.A.store(18);
    
    // 18 - 10 = 8
    alu::sub_operation(c, test_operand);
    ASSERT_EQ(c.A.load(), 8);
}

TEST(ALU, SUB_CARRY)
{
    cpu c;
    test_operand<byte> test_operand(10);
    c.A.store(0);
    
    alu::sub_operation(c, test_operand);

    ASSERT_EQ(c.A.load(), 255);
    ASSERT_EQ(c.F.carry(), true);
}

TEST(ALU, SUB_HALFCARRY)
{
    cpu c;
    c.A.store(0b00010000);
    test_operand<byte> test_operand(1);
    alu::sub_operation(c, test_operand);

    ASSERT_EQ(c.A.load(), 15);
    ASSERT_EQ(c.F.half_carry(), true);
}

TEST(ALU, SBC_CARRY_TRUE)
{
    cpu c;
    c.F.carry(true);
    c.A.store(10);
    test_operand<byte> test_operand(2);
    alu::sbc_operation(c, test_operand);
    ASSERT_EQ(c.A.load(), 7);
}

TEST(ALU, AND)
{
    cpu c;
    c.A.store(0b1010);
    test_operand<byte> test_operand(0b0101);

    alu::and_operation(c, test_operand);

    ASSERT_EQ(c.A.load(), 0);
    ASSERT_EQ(c.F.zero(), true);
}

TEST(ALU, OR)
{
    cpu c;
    c.A.store(0b1010);
    test_operand<byte> test_operand(0b0101);

    alu::or_operation(c, test_operand);

    ASSERT_EQ(c.A.load(), 0b1111);
    ASSERT_EQ(c.F.zero(), false);
}

TEST(ALU, XOR)
{
    cpu c;
    c.A.store(0b1110);
    test_operand<byte> test_operand(0b1101);

    alu::xor_operation(c, test_operand);

    ASSERT_EQ(c.A.load(), 0b0011);
    ASSERT_EQ(c.F.zero(), false);
}

TEST(ALU, CP_EQUALS)
{
    cpu c;
    c.A.store(10);
    test_operand<byte> test_operand(10);
    
    alu::cp_operation(c, test_operand);
    
    ASSERT_EQ(c.F.zero(), true);
    ASSERT_EQ(c.F.carry(), false);
}

TEST(ALU, CP_GREATER)
{
    cpu c;
    c.A.store(0);
    test_operand<byte> test_operand(1);

    alu::cp_operation(c, test_operand);

    ASSERT_EQ(c.F.zero(), false);
    ASSERT_EQ(c.F.carry(), true);
}

TEST(ALU, CP_LOWER)
{
    cpu c;
    c.A.store(100);
    test_operand<byte> test_operand(50);

    alu::cp_operation(c, test_operand);

    ASSERT_EQ(c.F.zero(), false);
    ASSERT_EQ(c.F.carry(), false);
}


TEST(ALU, INC_NORMAL)
{
    cpu c;
    test_operand<byte> test_operand(10);

    alu::inc_operation(c, test_operand);

    ASSERT_EQ(c.F.zero(), false);
    ASSERT_EQ(test_operand.value, 11);
}

TEST(ALU, INC_HALF_CARRY)
{
    cpu c;
    test_operand<byte> test_operand(0b1111);

    alu::inc_operation(c, test_operand);

    ASSERT_EQ(c.F.half_carry(), true);
}

TEST(ALU, INC_ZERO)
{
    cpu c;
    test_operand<byte> test_operand(255);

    alu::inc_operation(c, test_operand);

    ASSERT_EQ(c.F.zero(), true);
    ASSERT_EQ(c.F.carry(), true);
}

TEST(ALU, DEC_NORMAL)
{
    cpu c;
    test_operand<byte> test_operand(10);

    alu::dec_operation(c, test_operand);

    ASSERT_EQ(test_operand.value, false);
    ASSERT_EQ(c.F.zero(), false);
}

TEST(ALU, DEC_HALF_CARRY)
{
    cpu c;
    test_operand<byte> test_operand(0b00010000);

    alu::dec_operation(c, test_operand);

    ASSERT_EQ(test_operand.value, 0xF);
    ASSERT_EQ(c.F.zero(), false);
    ASSERT_EQ(c.F.half_carry(), true);
}

TEST(ALU, DEC_ZERO)
{
    cpu c;
    test_operand<byte> test_operand(1);

    alu::dec_operation(c, test_operand);

    ASSERT_EQ(test_operand.value, 0);
    ASSERT_EQ(c.F.zero(), true);
}
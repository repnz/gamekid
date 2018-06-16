#include "pch.h"

#include <GameKid/cpu/instructions/rotation.h>
#include <GameKid.Test/test_operand.h>

TEST(ROTATION, RL_TURN_OFF_CARRY)
{
    cpu c;
    c.F.carry(true);
    test_operand<byte> test_val(1);

    // 1 rl = 2
    rotation::rl_operation(c, test_val);

    ASSERT_EQ(test_val.value, 2);
    ASSERT_EQ(c.F.carry(), false);
}

TEST(ROTATION, RL_TURN_CARRY_ON)
{
    
    cpu c;
    test_operand<byte> test_val(128);

    // 128 rl = 1
    rotation::rl_operation(c, test_val);

    ASSERT_EQ(test_val.value, 1);
    ASSERT_EQ(c.F.carry(), true);
}

TEST(ROTATION, RLC_TURN_CARRY_ON)
{
    cpu c;

    // 128 rlc[carry = 0] = 0
    test_operand<byte> test_val(1 << 7);
    rotation::rlc_operation(c, test_val);

    ASSERT_EQ(test_val.value, 0);
    ASSERT_EQ(c.F.carry(), true);
}

TEST(ROTATION, RLC_CARRY_ON)
{
    cpu c;
    // 1 rlc (carry = 1) = 3
    c.F.carry(true);
    
    test_operand<byte> test_val(1);
    rotation::rlc_operation(c, test_val);

    ASSERT_EQ(test_val.value, 3);
    ASSERT_EQ(c.F.carry(), false);
}


TEST(ROTATION, RR_CARRY_ON)
{
    cpu c;

    // 1 rr == 128
    test_operand<byte> test_val(1);
    rotation::rr_operation(c, test_val);

    ASSERT_EQ(test_val.value, 128);
    ASSERT_EQ(c.F.carry(), true);
}

TEST(ROTATION, RR_CARRY_OFF)
{
    cpu c;

    // 128 rr == 64
    c.F.carry(true);
    
    test_operand<byte> test_val(128);
    rotation::rr_operation(c, test_val);

    ASSERT_EQ(test_val.value, 64);
    ASSERT_EQ(c.F.carry(), false);
}

TEST(ROTATION, RRC_CARRY_OFF)
{
    cpu c;

    // 1 rrc (carry = 0) == 0
    test_operand<byte> test_val(1);
    rotation::rrc_operation(c, test_val);

    ASSERT_EQ(test_val.value, 0);
    ASSERT_EQ(c.F.carry(), true);

}

TEST(ROTATION, RRC_CARRY_ON)
{
    cpu c;

    // 128 rrc (carry = 1) = 192
    c.F.carry(true);
    test_operand<byte> test_val(128);
    rotation::rrc_operation(c, test_val);

    ASSERT_EQ(test_val.value, 192);
    ASSERT_EQ(c.F.carry(), false);
}

TEST(ROTATION, SLA_TURN_CARRY_TRUE)
{
    cpu c;
    test_operand<byte> test_val(128);
    
    // 128 sla == 0
    rotation::sla_operation(c, test_val);

    ASSERT_EQ(test_val.value, 0);
    ASSERT_EQ(c.F.carry(), true);
}

TEST(ROTATION, SLA_TURN_CARRY_OFF)
{
    cpu c;
    c.F.carry(true);
    test_operand<byte> test_val(64);

    // 64 sla == 128
    rotation::sla_operation(c, test_val);

    ASSERT_EQ(test_val.value, 128);
    ASSERT_EQ(c.F.carry(), false);
}

TEST(ROTATION, SRA_TURN_CARRY_ON)
{
    cpu c;
    test_operand<byte> test_val(1);

    // 1 sra = 0
    rotation::sra_operation(c, test_val);

    ASSERT_EQ(test_val.value, 0);
    ASSERT_EQ(c.F.carry(), true);
}

TEST(ROTATION, SRA_KEEP_SIGNED_VALUE)
{
    cpu c;
    c.F.carry(false);
    test_operand<byte> test_val(0b10000000);
    
    // -128 sra = -64
    rotation::sra_operation(c, test_val);

    ASSERT_EQ(test_val.value, 0b11000000); // -64
    ASSERT_EQ(c.F.carry(), false);
}

TEST(ROTATION, SRL_TURN_CARRY_ON)
{
    cpu c;
    test_operand<byte> test_val(1);

    // 1 srl = 0
    rotation::srl_operation(c, test_val);

    ASSERT_EQ(test_val.value, 0);
    ASSERT_EQ(c.F.carry(), true);
}

TEST(ROTATION, SRL_CHANGE_SIGNED)
{
    cpu c;
    test_operand<byte> test_val(128);
    
    // 128 srl = 64
    rotation::srl_operation(c, test_val);

    ASSERT_EQ(test_val.value, 64);
    ASSERT_EQ(c.F.carry(), false);
}
#include "pch.h"
#include <GameKid/cpu/instructions/bitmask.h>
#include "test_operand.h"
#include <GameKid/cpu/operand/constant_operand.h>

TEST(BITMASK_OPCODES, BIT_TRUE_TURN_ZERO_OFF)
{
    cpu c;

    test_operand<byte> test_val(1);
    constant_operand bit_val(0);
    
    bitmask::bit_operation(c, bit_val, test_val);

    ASSERT_EQ(c.F.zero(), false);

}

TEST(BITMASK_OPCODES, BIT_FALSE_TURN_ZERO_ON)
{
    cpu c;

    test_operand<byte> test_val(1);
    constant_operand bit_val(1);

    bitmask::bit_operation(c, bit_val, test_val);

    ASSERT_EQ(c.F.zero(), true);
}

TEST(BITMASK_OPCODES, SET)
{
    cpu c;

    test_operand<byte> test_val(0);
    constant_operand bit_val(3);

    // 0 set 3 => 0b00001000 => 8
    bitmask::set_operation(c, bit_val, test_val);

    ASSERT_EQ(test_val.value, 8);
}


TEST(BITMASK_OPCODES, RES)
{
    cpu c;

    test_operand<byte> test_val(6);
    constant_operand bit_val(2);

    // 6 res 3 == 2
    bitmask::res_operation(c, bit_val, test_val);

    ASSERT_EQ(test_val.value, 2);
}

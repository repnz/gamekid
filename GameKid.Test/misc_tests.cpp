#include "pch.h"
#include <GameKid/cpu.h>
#include <GameKid/cpu/instructions/misc.h>
#include "test_operand.h"

TEST(MISC, SWAP)
{
    cpu c;
    
    test_operand<byte> test_val(0b00001111);
    misc::swap_operation(c, test_val);

    ASSERT_EQ(test_val.value, 0b11110000);
    ASSERT_EQ(c.F.zero(), false);

    test_val.value = 0b10100101;
    misc::swap_operation(c, test_val);

    ASSERT_EQ(test_val.value, 0b01011010);
    ASSERT_EQ(c.F.zero(), false);

    test_val.value = 0;
    misc::swap_operation(c, test_val);
    ASSERT_EQ(c.F.zero(), true);
}
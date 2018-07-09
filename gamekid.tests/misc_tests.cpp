#include "pch.h"
#include <gamekid/cpu/cpu.h>
#include <gamekid/cpu/impl/misc.h>
#include "test_operand.h"

using gamekid::cpu::impl::misc;

TEST(MISC, SWAP) {
    gamekid::system sys;
    gamekid::cpu::cpu& cpu = sys.cpu();    
    test_operand<byte> test_val(0b00001111);
    misc::swap_operation(cpu, test_val);

    ASSERT_EQ(test_val.value, 0b11110000);
    ASSERT_EQ(cpu.F.zero(), false);

    test_val.value = 0b10100101;
    misc::swap_operation(cpu, test_val);

    ASSERT_EQ(test_val.value, 0b01011010);
    ASSERT_EQ(cpu.F.zero(), false);

    test_val.value = 0;
    misc::swap_operation(cpu, test_val);
    ASSERT_EQ(cpu.F.zero(), true);
}
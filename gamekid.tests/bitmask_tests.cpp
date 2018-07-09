#include "pch.h"
#include <gamekid/system.h>
#include <gamekid/cpu/impl/bitmask.h>
#include "test_operand.h"
#include <gamekid/cpu/operands/constant_operand.h>

using gamekid::cpu::impl::bitmask;

TEST(BITMASK_OPCODES, BIT_TRUE_TURN_ZERO_OFF) {
    // Arrange
    gamekid::system sys;
    gamekid::cpu::cpu& cpu = sys.cpu();
    test_operand<byte> test_val(1);
    gamekid::cpu::operands::constant_operand bit_val(0);
    
    // Act
    bitmask::bit_operation(cpu, bit_val, test_val);

    // Assert
    ASSERT_EQ(cpu.F.zero(), false);

}

TEST(BITMASK_OPCODES, BIT_FALSE_TURN_ZERO_ON) {
    // Arrange
    gamekid::system sys;
    gamekid::cpu::cpu& cpu = sys.cpu();
    test_operand<byte> test_val(1);
    gamekid::cpu::operands::constant_operand bit_val(1);

    // Act
    bitmask::bit_operation(cpu, bit_val, test_val);

    // Assert
    ASSERT_EQ(cpu.F.zero(), true);
}

TEST(BITMASK_OPCODES, SET) {
    // Arrange
    gamekid::system sys;
    gamekid::cpu::cpu& cpu = sys.cpu();
    test_operand<byte> test_val(0);
    gamekid::cpu::operands::constant_operand bit_val(3);

    // Act
    bitmask::set_operation(cpu, bit_val, test_val);

    // Assert
    // 0 set 3 => 0b00001000 => 8
    ASSERT_EQ(test_val.value, 8);
}


TEST(BITMASK_OPCODES, RES) {
    // Arrange
    gamekid::system sys;
    gamekid::cpu::cpu& cpu = sys.cpu();
    test_operand<byte> test_val(6);
    gamekid::cpu::operands::constant_operand bit_val(2);

    
    // Act
    bitmask::res_operation(cpu, bit_val, test_val);

    // Assert
    // 6 res 3 == 2
    ASSERT_EQ(test_val.value, 2);
}

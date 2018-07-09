#include "pch.h"
#include "test_operand.h"
#include <gamekid/cpu/impl/alu.h>
#include <gamekid/system.h>

using gamekid::cpu::impl::alu;

namespace gamekid::tests {
    TEST(ALU_OPCODES, ADD_NORMAL) {
        // Arrange
        gamekid::system sys;
        gamekid::cpu::cpu& cpu = sys.cpu();
        test_operand<byte> test_operand(10);

        // Act
        alu::add_operation(cpu, test_operand);

        // Assert
        ASSERT_EQ(cpu.A.load(), 10);
    }

    TEST(ALU_OPCODES, ADD_CARRY_ON) {
        // Arrange
        gamekid::system sys;
        gamekid::cpu::cpu& cpu = sys.cpu();
        cpu.A.store(1);
        test_operand<byte> test_operand(255);

        // Act
        alu::add_operation(cpu, test_operand);

        // Assert
        ASSERT_EQ(cpu.A.load(), 0);
        ASSERT_EQ(cpu.F.carry(), true);
    }

    TEST(ALU_OPCODES, ADD_HALF_CARRY_ON) {
        // Arrange
        gamekid::system sys;
        gamekid::cpu::cpu& cpu = sys.cpu();
        cpu.A.store(1);
        test_operand<byte> test_operand(0b00001111);

        // Act
        alu::add_operation(cpu, test_operand);

        // Assert
        ASSERT_EQ(cpu.A.load(), 16);
        ASSERT_EQ(cpu.F.half_carry(), true);
    }

    TEST(ALU_OPCODES, ADC_CARRY_TRUE) {

        // Arrange
        gamekid::system sys;
        gamekid::cpu::cpu& cpu = sys.cpu();
        cpu.A.store(1);
        cpu.F.carry(true);
        test_operand<byte> test_operand(10);

        // Act
        alu::adc_operation(cpu, test_operand);

        // Assert
        // A[=1] + 10 + carry_flag[=1] = 12
        ASSERT_EQ(cpu.A.load(), 12);
    }

    TEST(ALU_OPCODES, ADC_CARRY_FALSE) {

        // Arrange
        gamekid::system sys;
        gamekid::cpu::cpu& cpu = sys.cpu();
        cpu.A.store(1);
        cpu.F.carry(false);
        test_operand<byte> test_operand(10);

        // Act
        alu::adc_operation(cpu, test_operand);

        // Assert
        // A[=1] + 10 + carry[=1] = 12
        ASSERT_EQ(cpu.A.load(), 11);
    }

    TEST(ALU_OPCODES, SUB_NORMAL) {
        // Arrange
        gamekid::system sys;
        gamekid::cpu::cpu& cpu = sys.cpu();
        test_operand<byte> test_operand(10);
        cpu.A.store(18);

        // Act
        alu::sub_operation(cpu, test_operand);

        // Assert
        // 18 - 10 = 8
        ASSERT_EQ(cpu.A.load(), 8);
    }

    TEST(ALU_OPCODES, SUB_CARRY) {
        // Arrange
        gamekid::system sys;
        gamekid::cpu::cpu& cpu = sys.cpu();
        test_operand<byte> test_operand(1);
        cpu.A.store(0);

        // Act
        alu::sub_operation(cpu, test_operand);

        // Assert
        ASSERT_EQ(cpu.A.load(), 255);
        ASSERT_EQ(cpu.F.carry(), true);
    }

    TEST(ALU_OPCODES, SUB_HALFCARRY) {

        // Arrange
        gamekid::system sys;
        gamekid::cpu::cpu& cpu = sys.cpu();
        cpu.A.store(0b00010000);
        test_operand<byte> test_operand(1);

        // Act
        alu::sub_operation(cpu, test_operand);

        // Assert
        ASSERT_EQ(cpu.A.load(), 15);
        ASSERT_EQ(cpu.F.half_carry(), true);
    }

    TEST(ALU_OPCODES, SBC_CARRY_TRUE) {
        // Arrange
        gamekid::system sys;
        gamekid::cpu::cpu& cpu = sys.cpu();
        cpu.F.carry(true);
        cpu.A.store(10);
        test_operand<byte> test_operand(2);

        // Act
        alu::sbc_operation(cpu, test_operand);

        // Assert
        ASSERT_EQ(cpu.A.load(), 7);
    }

    TEST(ALU_OPCODES, AND) {
        // Arrange
        gamekid::system sys;
        gamekid::cpu::cpu& cpu = sys.cpu();
        cpu.A.store(0b1010);
        test_operand<byte> test_operand(0b0101);

        // Act
        alu::and_operation(cpu, test_operand);

        // Assert
        ASSERT_EQ(cpu.A.load(), 0);
        ASSERT_EQ(cpu.F.zero(), true);
    }

    TEST(ALU_OPCODES, OR) {

        // Arrange
        gamekid::system sys;
        gamekid::cpu::cpu& cpu = sys.cpu();
        cpu.A.store(0b1010);
        test_operand<byte> test_operand(0b0101);

        // Act
        alu::or_operation(cpu, test_operand);

        // Assert
        ASSERT_EQ(cpu.A.load(), 0b1111);
        ASSERT_EQ(cpu.F.zero(), false);
    }

    TEST(ALU_OPCODES, XOR) {

        // Arrange
        gamekid::system sys;
        gamekid::cpu::cpu& cpu = sys.cpu();
        cpu.A.store(0b1110);
        test_operand<byte> test_operand(0b1101);

        // Act
        alu::xor_operation(cpu, test_operand);

        // Assert
        ASSERT_EQ(cpu.A.load(), 0b0011);
        ASSERT_EQ(cpu.F.zero(), false);
    }

    TEST(ALU_OPCODES, CP_EQUALS) {

        // Arrange 
        gamekid::system sys;
        gamekid::cpu::cpu& cpu = sys.cpu();
        cpu.A.store(10);
        test_operand<byte> test_operand(10);

        // Act
        alu::cp_operation(cpu, test_operand);

        // Assert
        ASSERT_EQ(cpu.F.zero(), true);
        ASSERT_EQ(cpu.F.carry(), false);
    }

    TEST(ALU_OPCODES, CP_GREATER) {

        // Arrange
        gamekid::system sys;
        gamekid::cpu::cpu& cpu = sys.cpu();
        cpu.A.store(0);
        test_operand<byte> test_operand(1);

        // Act 
        alu::cp_operation(cpu, test_operand);

        // Assert
        ASSERT_EQ(cpu.F.zero(), false);
        ASSERT_EQ(cpu.F.carry(), true);
    }

    TEST(ALU_OPCODES, CP_LOWER) {
        // Assert
        gamekid::system sys;
        gamekid::cpu::cpu& cpu = sys.cpu();
        cpu.A.store(100);
        test_operand<byte> test_operand(50);

        // Act
        alu::cp_operation(cpu, test_operand);

        // Assert
        ASSERT_EQ(cpu.F.zero(), false);
        ASSERT_EQ(cpu.F.carry(), false);
    }


    TEST(ALU, INC_NORMAL) {
        // Arrage 
        gamekid::system sys;
        gamekid::cpu::cpu& cpu = sys.cpu();
        test_operand<byte> test_operand(10);

        // Act
        alu::inc_operation(cpu, test_operand);

        // Assert
        ASSERT_EQ(cpu.F.zero(), false);
        ASSERT_EQ(test_operand.value, 11);
    }

    TEST(ALU, INC_HALF_CARRY) {
        // Arrange
        gamekid::system sys;
        gamekid::cpu::cpu& cpu = sys.cpu();
        test_operand<byte> test_operand(0b1111);

        // Act
        alu::inc_operation(cpu, test_operand);

        // Assert
        ASSERT_EQ(cpu.F.half_carry(), true);
    }

    TEST(ALU, INC_ZERO) {
        // Arrange
        gamekid::system sys;
        gamekid::cpu::cpu& cpu = sys.cpu();
        test_operand<byte> test_operand(255);

        // Act
        alu::inc_operation(cpu, test_operand);

        // Assert
        ASSERT_EQ(cpu.F.zero(), true);
    }

    TEST(ALU, DEC_NORMAL) {
        // Arrange
        gamekid::system sys;
        gamekid::cpu::cpu& cpu = sys.cpu();
        test_operand<byte> test_operand(10);

        // Act
        alu::dec_operation(cpu, test_operand);

        // Assert
        ASSERT_EQ(test_operand.value, 9);
        ASSERT_EQ(cpu.F.zero(), false);
        ASSERT_EQ(cpu.F.half_carry(), false);
    }

    TEST(ALU, DEC_HALF_CARRY) {
        // Arrange
        gamekid::system sys;
        gamekid::cpu::cpu& cpu = sys.cpu();
        test_operand<byte> test_operand(0b00010000);

        // Act
        alu::dec_operation(cpu, test_operand);

        // Assert
        ASSERT_EQ(test_operand.value, 0xF);
        ASSERT_EQ(cpu.F.zero(), false);
        ASSERT_EQ(cpu.F.half_carry(), true);
    }

    TEST(ALU, DEC_ZERO) {
        // Arrange
        gamekid::system sys;
        gamekid::cpu::cpu& cpu = sys.cpu();
        test_operand<byte> test_operand(1);

        // Act
        alu::dec_operation(cpu, test_operand);

        // Assert
        ASSERT_EQ(test_operand.value, 0);
        ASSERT_EQ(cpu.F.zero(), true);
    }
}
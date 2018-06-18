#include "pch.h"
#include <GameKid/cpu/operand.h>
#include <GameKid/cpu/instructions/mem/mem_operands.h>

void assert_vector(const std::vector<byte>& expected, const std::vector<byte>& actual)
{
    ASSERT_EQ(expected, actual);
}

TEST(OPERANDS, IMMIDIATE_BYTES)
{
    assert_vector({ 0xFF}, immidiate_bytes<byte>("255"));
    assert_vector({ 0xFF, 0x00}, immidiate_bytes<word>("255"));
    assert_vector({ 0x00 }, immidiate_bytes<byte>("0"));
    assert_vector({ 0x01, 0x02}, immidiate_bytes<word>("513"));
}
#include "pch.h"
#include <GameKid/cpu/operand.h>
#include <GameKid/cpu/instructions/mem/mem_operands.h>
#include "test_tools.h"

TEST(OPERANDS, IMMIDIATE_BYTES)
{
    assert_equals({ 0xFF}, immidiate_bytes<byte>("255"));
    assert_equals({ 0xFF, 0x00}, immidiate_bytes<word>("255"));
    assert_equals({ 0x00 }, immidiate_bytes<byte>("0"));
    assert_equals({ 0x01, 0x02}, immidiate_bytes<word>("513"));
}
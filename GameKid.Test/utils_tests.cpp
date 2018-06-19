#include "pch.h"
#include <GameKid/utils/str.h>
#include <GameKid/utils/bytes.h>
#include <GameKid/utils/bits.h>
#include "test_tools.h"

TEST(UTILS, STRING_SPLIT)
{
    std::vector<std::string> result = string_tools::split("hello world", ' ');
    assert_equals({ "hello", "world" }, result);
}

TEST(UTILS, STRING_JOIN)
{
    std::string result = string_tools::join(std::vector<std::string> { "hello", "world"});
    assert_equals<std::string>("hello, world", result);
}

TEST(UTILS, LITTLE_ENDIAN_ENCODE)
{
    std::vector<byte> result;
    
    result = bytes::little_endian_encode<byte>(0x10);
    assert_equals<std::vector<byte>>({ 0x10 }, result);

    result = bytes::little_endian_encode<word>(0x10);
    assert_equals<std::vector<byte>>({ 0x10, 0x00 }, result);

    result = bytes::little_endian_encode<word>(0x100);
    assert_equals<std::vector<byte>>({ 0x00, 0x01}, result);
}

TEST(UTILS, LITTLE_ENDIAN_DECODE)
{
    assert_equals<byte>(0x10, bytes::little_endian_decode<byte>({ 0x10 }));

    assert_equals<word>(0x10, bytes::little_endian_decode<word>({ 0x10 , 0x00}));

    assert_equals<word>(0x100, bytes::little_endian_decode<word>({ 0x00 , 0x01 }));
}

TEST(UTILS, SET_BIT) 
{
    ASSERT_EQ(0x8f, bits::set_bit<byte>(0x0f, 7, true));
    ASSERT_EQ(0x0f, bits::set_bit<byte>(0x8f, 7, false));
}
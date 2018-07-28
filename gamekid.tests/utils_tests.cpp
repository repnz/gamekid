#include "pch.h"
#include <gamekid/utils/str.h>
#include <gamekid/utils/bytes.h>
#include <gamekid/utils/bits.h>
#include "test_tools.h"

namespace gamekid::tests {
    TEST(UTILS, STRING_SPLIT) {
        std::vector<std::string> result = utils::str::split("hello world", ' ');
        assert_equals({ "hello", "world" }, result);
    }

    TEST(UTILS, STRING_JOIN) {
        std::string result = utils::str::join(std::vector<std::string> { "hello", "world"});
        assert_equals<std::string>("hello, world", result);
    }

    TEST(UTILS, LITTLE_ENDIAN_ENCODE) {
        std::vector<byte> result;

        result = utils::bytes::little_endian_encode<byte>(0x10);
        assert_equals<std::vector<byte>>({ 0x10 }, result);

        result = utils::bytes::little_endian_encode<word>(0x10);
        assert_equals<std::vector<byte>>({ 0x10, 0x00 }, result);

        result = utils::bytes::little_endian_encode<word>(0x100);
        assert_equals<std::vector<byte>>({ 0x00, 0x01 }, result);
    }

    TEST(UTILS, LITTLE_ENDIAN_DECODE) {
        assert_equals<byte>(0x10, utils::bytes::little_endian_decode<byte>({ 0x10 }));

        assert_equals<word>(0x10, utils::bytes::little_endian_decode<word>({ 0x10 , 0x00 }));

        assert_equals<word>(0x100, utils::bytes::little_endian_decode<word>({ 0x00 , 0x01 }));

        assert_equals<byte>(0x10, utils::bytes::little_endian_decode<byte>({ 0x10 , 0x00 }));

        assert_equals<word>(0x110, utils::bytes::little_endian_decode<word>({ 0x10 , 0x01, 0x00 }));
    }

    TEST(OPERANDS, LITTLE_ENDIAN_ENCODE_STR) {
        assert_equals({ 0xFF }, utils::bytes::little_endian_encode_str<byte>("255"));
        assert_equals({ 0xFF, 0x00 }, utils::bytes::little_endian_encode_str<word>("255"));
        assert_equals({ 0x00 }, utils::bytes::little_endian_encode_str<byte>("0"));
        assert_equals({ 0x01, 0x02 }, utils::bytes::little_endian_encode_str<word>("513"));
    }

    TEST(UTILS, SET_BIT) {
        ASSERT_EQ(0x8f, utils::bits::set_bit<byte>(0x0f, 7, true));
        ASSERT_EQ(0x0f, utils::bits::set_bit<byte>(0x8f, 7, false));
    }

    TEST(UTILS, CHECK_CARRY_UP) {
        ASSERT_EQ(true, utils::bits::check_carry_up(0xFF, 0x00, 7));
        ASSERT_EQ(false, utils::bits::check_carry_up(0xFF, 0x100, 8));
    }

    TEST(UTILS, CHECK_CARRY_DOWN) {
        ASSERT_EQ(true, utils::bits::check_carry_down(0x00, 0xFF, 7));
        ASSERT_EQ(false, utils::bits::check_carry_down(0xFF, 0xFE, 8));
    }

    TEST(UTILS, TEST_BITS_ARRAY) {
        
        std::array<byte, 16> bytes;

        for (byte i = 0; i < 16; ++i) {
            bytes[i] = i;
        }

        using colors_array = utils::bits::bits_array<2, 64>;

        colors_array arr(bytes);
        
        for (byte i=0; i<16; ++i) {
            ASSERT_EQ(bytes[i] >> 6 & 0b11, arr.get(i*4+0));
            ASSERT_EQ(bytes[i] >> 4 & 0b11, arr.get(i*4+1));
            ASSERT_EQ(bytes[i] >> 2 & 0b11, arr.get(i*4+2));
            ASSERT_EQ(bytes[i] >> 0 & 0b11, arr.get(i*4+3));
        }

    }
}
#include "bytes.h"

using namespace gamekid::utils;

std::vector<byte> bytes::little_endian_encode(int value, int size_in_bytes) {
    std::vector<byte> value_in_bytes(size_in_bytes);

    for (byte i = 0; i<size_in_bytes; ++i) {
        value_in_bytes[i] = (value & 0xFF);
        value >>= 8;
    }

    return value_in_bytes;
}
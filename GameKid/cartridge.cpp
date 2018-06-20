#include "cartridge.h"

byte calculate_header_checksum(byte* data)
{
    byte checksum = 0;

    for (int i = 0x134; i < 0x14c; ++i)
    {
        checksum -= data[i] - 1;
    }

    return checksum;
}
bool validate_header_checksum(byte * data)
{
    byte actual = calculate_header_checksum(data);
    byte checksum = data[cartridge_offsets::header_checksum.start];

    return (checksum == actual);
}


#include "cartridge.h"

byte cartridge::calculate_header_checksum(const byte* data) {
    byte checksum = 0;

    for (int i = 0x134; i < 0x14c; ++i) {
        checksum -= data[i] - 1;
    }

    return checksum;
}

bool cartridge::validate_header_checksum(const byte * data) {
    byte actual = cartridge::calculate_header_checksum(data);
    byte checksum = data[cartridge_offsets::header_checksum.start];

    return (checksum == actual);
}

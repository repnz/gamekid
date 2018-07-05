#include "checksum.h"
#include "header_offsets.h"

byte gamekid::rom::checksum::calculate_header_checksum(const byte* data) {
    byte checksum = 0;

    for (int i = 0x134; i < 0x14c; ++i) {
        checksum -= data[i] - 1;
    }

    return checksum;
}

bool gamekid::rom::checksum::validate_header_checksum(const byte * data) {
    byte actual = checksum::calculate_header_checksum(data);
    byte checksum = data[header_offsets::header_checksum.start];

    return (checksum == actual);
}

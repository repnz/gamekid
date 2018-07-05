#pragma once
#include <gamekid/utils/types.h>

namespace gamekid::rom::checksum {
    byte calculate_header_checksum(const byte* data);
    bool validate_header_checksum(const byte* data);
}
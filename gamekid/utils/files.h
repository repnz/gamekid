#pragma once
#include <vector>
#include <gamekid/utils/types.h>

namespace gamekid::utils::files {
    std::vector<byte> read_file(const std::string& fileName);
}
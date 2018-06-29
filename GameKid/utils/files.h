#pragma once
#include <vector>
#include <GameKid/cpu_types.h>

namespace files {
    std::vector<byte> read_file(const std::string& fileName);
}
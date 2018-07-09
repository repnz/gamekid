#pragma once
#include <array>
#include "page.h"

namespace gamekid::memory {
    class memory_map {
    public:
        std::array<page*, 256> pages;
        virtual ~memory_map() = default;
    };
}

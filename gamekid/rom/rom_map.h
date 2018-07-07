#pragma once
#include <vector>
#include "gamekid/memory/page.h"

namespace gamekid::rom {
    class rom_map {
    public:
        virtual void fill_pages(memory::page** pages) = 0;
        virtual memory::page* get_page(size_t index) = 0;
        virtual ~rom_map() = default;
    };
}

#pragma once
#include "rom_map.h"
#include "cartridge.h"
#include "gamekid/memory/view_page.h"
#include <vector>

namespace gamekid::rom {
    class rom_only_map : public rom_map {
    private:
        std::vector<memory::view_page> _cart_view_pages;
    public:
        explicit rom_only_map(const cartridge& cart);
        memory::page* get_page(size_t index) override;
        void fill_pages(memory::page** pages) override;
    };
}

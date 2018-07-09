#pragma once
#include "gamekid/rom/rom_map.h"
#include <gamekid/memory/normal_page.h>

namespace gamekid::tests {
    class test_rom_map : public gamekid::rom::rom_map {
    private:
        std::array<gamekid::memory::normal_page, 256> _pages;
    public:
        void fill_pages(std::array<gamekid::memory::page*, 256>& pages) override {
            for (size_t i = 0; i<256; ++i) {
                pages[i] = &_pages[i];
            }
        }

        gamekid::memory::page* get_page(size_t index) override {
            return &_pages[index];
        }
    };

}
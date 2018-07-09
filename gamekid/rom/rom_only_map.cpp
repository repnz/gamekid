#include "rom_only_map.h"

gamekid::rom::rom_only_map::rom_only_map(const cartridge & cart) {
    const byte* rom_ptr = cart.data().data();
    _cart_view_pages.reserve(128);

    for (size_t i=0; i<128; ++i) {
        _cart_view_pages.emplace_back(rom_ptr + (i * 256));
    }
}

gamekid::memory::page* gamekid::rom::rom_only_map::get_page(size_t index) {
    return &_cart_view_pages[index];
}

void gamekid::rom::rom_only_map::fill_pages(std::array<memory::page*, 256>& pages) {
    for (size_t i = 0; i < 128; ++i) {
        pages[i] = &_cart_view_pages[i];
    }
}

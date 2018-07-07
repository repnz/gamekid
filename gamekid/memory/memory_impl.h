#pragma once
#include "memory.h"
#include <vector>
#include <array>
#include "cell.h"
#include "page.h"
#include "normal_page.h"
#include "io_page.h"
#include "boot_rom_page.h"

namespace gamekid::memory {
    class memory_impl {
    private:
        const rom::cartridge& _rom;
        std::array<page*, 256> _pages{};
        std::array<normal_page, 128> _normal_pages;
        boot_rom_page _boot_rom_page;
        io_page _io_page;
        std::unique_ptr<rom::rom_map> _rom_map;
        static int page_index(const word address);
    public:
        explicit memory_impl(const rom::cartridge& rom);
        void initialize_cells();
        void store(word address, byte value);
        byte load(word address);
        void set_boot_rom_status(bool on);
    };
}

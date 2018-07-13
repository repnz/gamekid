#pragma once
#include <array>
#include "normal_page.h"
#include "memory_map.h"
#include "io_page.h"
#include "gamekid/rom/rom_map.h"
#include "boot_rom_page.h"

namespace gamekid::io::video {
    class lcd;
}

namespace gamekid::memory {
    
    class gameboy_memory_map : public memory_map {
    private:
        std::array<normal_page, 128> _normal_pages;
        boot_rom_page _boot_rom_page;
        io_page _io_page;
        rom::rom_map& _rom_map;
    public:
        explicit gameboy_memory_map(rom::rom_map& rom_map, io::video::lcd& lcd);
        void disable_boot_rom();
    };
}


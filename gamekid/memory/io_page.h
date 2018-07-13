#pragma once
#include "page.h"
#include <gamekid/io/joypad_cell.h>
#include <gamekid/io/boot_rom_status_cell.h>
#include <gamekid/io/lcd_control_cell.h>
#include <array>

namespace gamekid::io {
    class lcd;
}

namespace gamekid::memory {
    class gameboy_memory_map;

    class io_page : public page {
    private:
        io::joypad_cell _joypad_cell;
        io::boot_rom_status_cell _boot_rom_status_cell;
        io::lcd_control_cell _lcd_control;
        std::array<cell*, 256> _cells;

    public:
        static const word io_page_memory = 0xFF00;
        explicit io_page(gameboy_memory_map& memory_map, io::lcd& lcd);
        byte load(byte offset) override;
        void store(byte offset, byte value) override;
    };
}

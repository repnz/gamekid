#pragma once
#include "gamekid/memory/cell.h"

namespace gamekid::memory { class gameboy_memory_map; }

namespace gamekid::io {
    class boot_rom_status_cell : public memory::cell {
    private:
        memory::gameboy_memory_map& _memory;
    public:
        explicit boot_rom_status_cell(memory::gameboy_memory_map& memory);
        void store(byte value) override;
    };
}

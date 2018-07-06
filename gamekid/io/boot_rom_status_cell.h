#pragma once
#include "gamekid/memory/cell.h"

namespace gamekid::memory {
    class memory_impl;
}

namespace gamekid::io {
    class boot_rom_status_cell : public memory::cell {
    private:
        memory::memory_impl& _memory;
    public:
        explicit boot_rom_status_cell(memory::memory_impl& memory);
        void store(byte value) override;
    };
}

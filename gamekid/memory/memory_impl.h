#pragma once
#include "memory.h"
#include <vector>
#include <array>
#include "cell.h"
#include <gamekid/io/joypad_cell.h>

namespace gamekid::memory {
    class memory::impl {
    private:
        const std::vector<byte>& _rom;
        std::array<cell*, 64 * 1024> _cells;
        std::array<cell, 64 * 1024> _normal_cells;
        io::joypad_cell _joypad;
    public:
        explicit impl(const std::vector<byte>& rom);
        void initialize_cells();
        void store(word address, byte value);
        byte load(word address);
    };
}
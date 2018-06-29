#pragma once
#include "memory.h"
#include <vector>
#include <array>
#include "memory_cell.h"
#include <GameKid/io/joypad_cell.h>

class memory::impl {
private:
    const std::vector<byte>& _rom;
    std::array<memory_cell*, 64*1024> _cells;
    std::array<memory_cell, 64*1024> _normal_cells;
    joypad_cell _joypad;
public:
    explicit impl(const std::vector<byte>& rom);
    void initialize_cells();
    void store(word address, byte value);
    byte load(word address);
};

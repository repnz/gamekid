#include "boot_rom_status_cell.h"
#include <gamekid/memory/gameboy_memory_map.h>

gamekid::io::boot_rom_status_cell::boot_rom_status_cell(memory::gameboy_memory_map& memory)
: _memory(memory){
}

void gamekid::io::boot_rom_status_cell::store(byte value) {
    if (value != 0) {
        _memory.disable_boot_rom();
    } else {
        throw std::exception("Cannot enable boot rom again!");
    }

    cell::store(value);
}
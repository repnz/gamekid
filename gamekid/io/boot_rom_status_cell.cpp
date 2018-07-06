#include "boot_rom_status_cell.h"
#include <gamekid/memory/memory_impl.h>

gamekid::io::boot_rom_status_cell::boot_rom_status_cell(memory::memory_impl & memory)
: _memory(memory){
}

void gamekid::io::boot_rom_status_cell::store(byte value) {
    _memory.set_boot_rom_status(value == 0);
    cell::store(value);
}

#include "io_page.h"
#include "gamekid/io/io_registers.h"

gamekid::memory::io_page::io_page(memory_impl& memory) :
_boot_rom_status_cell(memory), 
_cells({}) {
    _cells[P1 - io_page_memory] = &_joypad_cell;
    _cells[ENABLE_BOOT_ROM - io_page_memory] = &_boot_rom_status_cell;
}

byte gamekid::memory::io_page::load(byte offset) {
    return _cells[offset]->load();
}

void gamekid::memory::io_page::store(byte offset, byte value) {
    _cells[offset]->store(value);
}

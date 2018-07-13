#include "io_page.h"
#include "gamekid/io/io_registers.h"

gamekid::memory::io_page::io_page(gameboy_memory_map& memory_map, io::video::lcd& lcd) :
_boot_rom_status_cell(memory_map), _lcd_control(lcd),
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

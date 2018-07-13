#include "gameboy_memory_map.h"
#include "memory_map_offsets.h"

using gamekid::memory::gameboy_memory_map;

gameboy_memory_map::gameboy_memory_map(gamekid::rom::rom_map& rom_map, gamekid::io::video::lcd& lcd): 
_io_page(*this, lcd), _rom_map(rom_map) {
    // Initialize hald of the pages with rom pages
    // Get the rom pages using the correct rom map
    _rom_map.fill_pages(pages);

    // Initialize half the pages with normal pages
    // Half of the pages are for the normal address space
    for (int i = 128; i < 256; ++i) {
        pages[i] = &_normal_pages[i - 128];
    }

    // Duplicate all the pages in the internal ram 
    const int internal_ram_index = page::index(memory_map_offsets::internal_ram_8kb);
    const int echo_ram_index = page::index(memory_map_offsets::internal_ram_8kb_echo);

    for (int i = 0; i<0x1e; ++i) {
        pages[internal_ram_index + i] =
            pages[echo_ram_index + i];
    }

    // Handle IO
    pages[io_page::io_page_memory >> 8] = &_io_page;
    pages[0] = &_boot_rom_page;
}

void gameboy_memory_map::disable_boot_rom() {
    pages[0] = _rom_map.get_page(0);
}
#include "memory_impl.h"
#include "memory_map.h"

using gamekid::memory::memory;

int gamekid::memory::memory_impl::page_index(const word address) {
    return address / 256;
}

gamekid::memory::memory_impl::memory_impl(const rom::cartridge& rom) : 
_rom(rom), _io_page(*this), _rom_map(rom.create_rom_map()) {
    initialize_cells();
}

void gamekid::memory::memory_impl::initialize_cells() {
    // Initialize hald of the pages with rom pages
    // Get the rom pages using the correct rom map
    _rom_map->fill_pages(_pages.data());

    // Initialize half the pages with normal pages
    // Half of the pages are for the normal address space
    for (int i = 128; i < 256; ++i) {
        _pages[i] = &_normal_pages[i - 128];
    }

    // Duplicate all the pages in the internal ram 
    const int internal_ram_index = page_index(memory_map::internal_ram_8kb);
    const int echo_ram_index  = page_index(memory_map::internal_ram_8kb_echo);

    for (int i=0; i<0x1e; ++i) {
        _pages[internal_ram_index +i] =
            _pages[echo_ram_index +i];
    }

    // Handle IO
    _pages[io_page::io_page_memory >> 8] = &_io_page;
    _pages[0] = &_boot_rom_page;
}

void gamekid::memory::memory_impl::store(word address, byte value){
    _pages[address>>8]->store(address & 0xFF, value);
}

byte gamekid::memory::memory_impl::load(word address){
    return _pages[address >> 8]->load(address & 0xFF);
}

void gamekid::memory::memory_impl::set_boot_rom_status(bool on) {
    if (on) {
        _pages[0] = &_boot_rom_page;
    } else {
        _pages[0] = _rom_map->get_page(0);
    }
}

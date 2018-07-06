#include "memory_impl.h"
#include "memory_map.h"
#include <gamekid/io/io_registers.h>

using gamekid::memory::memory;

int gamekid::memory::memory::impl::page_index(const word address) {
    return address / 256;
}

gamekid::memory::memory::impl::impl(const std::vector<byte>& rom) : _rom(rom) {
    initialize_cells();
}

void gamekid::memory::memory::impl::initialize_cells() {
    // initialize all the pages with normal pages
    for (int i = 0; i < 0xFF; ++i)  {
        _pages[i] = &_normal_pages[i];
    }

    // duplicate all the pages in the internal ram 
    const int internal_ram_index = page_index(memory_map::internal_ram_8kb);
    const int echo_ram_index  = page_index(memory_map::internal_ram_8kb_echo);

    for (int i=0; i<0x1e; ++i) {
        _pages[internal_ram_index +i] =
            _pages[echo_ram_index +i];
    }

    _pages[io_page::io_page_memory >> 8] = &_io_page;
}

void gamekid::memory::memory::impl::store(word address, byte value){
    _pages[address>>8]->store(address & 0xFF, value);
}

byte gamekid::memory::memory::impl::load(word address){
    return _pages[address >> 8]->load(address & 0xFF);
}

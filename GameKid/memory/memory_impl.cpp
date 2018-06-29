#include "memory_impl.h"
#include "memory_map.h"
#include <GameKid/io/io_registers.h>

memory::impl::impl(const std::vector<byte>& rom) : _rom(rom) {
    initialize_cells();
}

void memory::impl::initialize_cells() {
    // create all the normal cells
    for (int i = 0; i < 0xFFFF; ++i)  {
        _cells[i] = &_normal_cells[i];
    }

    // duplicate all the cells in the internal ram 
    for (int i=0; i<0x1e00; ++i) {
        _cells[memory_map::internal_ram_8kb + i] =
            _cells[memory_map::internal_ram_8kb_echo + i];
    }

    _cells[P1] = &_joypad;
}

void memory::impl::store(word address, byte value){
    _cells[address]->store(value);
}

byte memory::impl::load(word address){
    return _cells[address]->load();
}

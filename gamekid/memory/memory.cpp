#include "memory.h"
#include "memory_map_offsets.h"
#include "memory_map.h"

using gamekid::memory::memory;

gamekid::memory::memory::memory(memory_map& map) : _map(map){
}

byte gamekid::memory::memory::load_byte(word address) {
    return _map.pages[address >> 8]->load(address & 0xFF);
}

void gamekid::memory::memory::store_byte(word address, byte value) {
    _map.pages[address >> 8]->store(address & 0xFF, value);
}

void gamekid::memory::memory::store_word(word address, word value) {
    const byte* ptr = (byte*)&value;
    store_byte(address, ptr[0]);
    store_byte(address+1, ptr[1]);
}

word gamekid::memory::memory::load_word(word address) {
    return (load_byte(address + 1) << 8) | load_byte(address);
}
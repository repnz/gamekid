#include "memory.h"
#include <vector>
#include "memory_map.h"
#include "memory_impl.h"

using gamekid::memory::memory;

gamekid::memory::memory::memory(const std::vector<byte>& rom) : _impl(std::make_unique<memory_impl>(rom)) {
}

byte gamekid::memory::memory::load_byte(word address) {
    return _impl->load(address);
}

void gamekid::memory::memory::store_byte(word address, byte value) {
    _impl->store(address, value);
}

void gamekid::memory::memory::store_word(word address, word value) {
    const byte* ptr = (byte*)&value;
    store_byte(address, ptr[0]);
    store_byte(address+1, ptr[1]);
}

word gamekid::memory::memory::load_word(word address) {
    return (load_byte(address + 1) << 8) | load_byte(address);
}

gamekid::memory::memory::~memory() = default;
#include "memory.h"
#include <vector>
#include "memory_map.h"
#include "memory_impl.h"

memory::memory(const std::vector<byte>& rom) : _impl(std::make_unique<memory::impl>(rom)) {
}

byte memory::load_byte(word address) {
    return _impl->load(address);
}

void memory::store_byte(word address, byte value) {
    _impl->store(address, value);
}

void memory::store_word(word address, word value) {
    const byte* ptr = (byte*)&value;
    store_byte(address, ptr[0]);
    store_byte(address+1, ptr[1]);
}

word memory::load_word(word address) {
    return (load_byte(address + 1) << 8) | load_byte(address);
}

memory::~memory() = default;
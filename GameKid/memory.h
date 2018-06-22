#pragma once
#include "cpu_types.h"
#include "io/joypad.h"

namespace memory_map
{
    const word
        rom_bank_0 = 0,
        switchable_rom_bank_16kb = 0x4000,
        video_ram = 0x8000,
        switchable_rom_bank_32kb = 0xa000,
        internal_ram_8kb = 0xc000,
        internal_ram_8kb_echo = 0xe000,
        sprite_attribute_memory = 0xfe00,
        empty1 = 0xfea0,
        io_ports = 0xff00,
        empty2 = 0xfea0,
        internal_ram = 0xff80,
        interrupt_enable_register = 0xffff;

}

class memory
{
private:
    byte mem[64 * 1024];
    joypad _joypad;
public:
    memory();
    memory(const memory&) = delete;
    memory& operator=(memory&) = delete;

    template <typename T>
    T load(word address)
    {
        return *(T*)(mem[address]);
    }

    template <typename T>
    void store(word address, T value)
    {
        *(T*)(mem[address]) = value;
    }

    void store_byte(word address, byte value);
    byte load_byte(word address);
    word load_word_le(word address);
};

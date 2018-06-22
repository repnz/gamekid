#include "memory.h"
#include "io/io_registers.h"

memory::memory()
    : _joypad(&mem[P1])
{
}

void memory::store_byte(word address, byte value)
{
    mem[address] = value;

    // handle duplication of the 8kb internal ram
    if (address >= memory_map::internal_ram_8kb && address < memory_map::internal_ram_8kb+0x2000)
    {
        const word offset = address - memory_map::internal_ram_8kb;
        mem[memory_map::internal_ram_8kb_echo + offset] = value;
    }
    else if (address >= memory_map::internal_ram_8kb_echo && address < memory_map::internal_ram_8kb_echo+0x2000)
    {
        const word offset = address - memory_map::internal_ram_8kb_echo;
        mem[memory_map::internal_ram_8kb + offset] = value;
    }
    else if (address == P1)
    {
        _joypad.update(value);
    }
}

byte memory::load_byte(word address)
{
    return mem[address];
}

word memory::load_word_le(word address)
{
    return *(word*)mem[address];
}

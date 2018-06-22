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
    if (address >= 0xC000 && address < 0xDE00)
    {
        const word offset = address - 0xC000;
        mem[0xE000 + offset] = value;
    }
    else if (address >= 0xE000 && address < 0xFE00)
    {
        const word offset = address - 0xE000;
        mem[0xC000] = value;
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

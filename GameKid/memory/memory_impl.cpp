#include "memory_impl.h"
#include "memory_map.h"
#include <GameKid/io/io_registers.h>

memory::impl::impl(const std::vector<byte>& rom) : _rom(rom), _joypad(&_ram[P1])
{
}

void memory::impl::store(word address, byte value)
{
    _ram[address] = value;

    // handle duplication of the 8kb internal ram
    if (address >= memory_map::internal_ram_8kb &&
        address < memory_map::internal_ram_8kb + 0x2000)
    {
        const word offset = address - memory_map::internal_ram_8kb;
        _ram[memory_map::internal_ram_8kb_echo + offset] = value;
    }
    else if (address >= memory_map::internal_ram_8kb_echo &&
        address < memory_map::internal_ram_8kb_echo + 0x2000)
    {
        const word offset = address - memory_map::internal_ram_8kb_echo;
        _ram[memory_map::internal_ram_8kb + offset] = value;
    }
    else if (address == P1)
    {
        _joypad.update(value);
    }
}

byte memory::impl::load(word address)
{
    if (_ram[ENABLE_BOOT_ROM] && address >= 0 && address <= memory_map::video_ram)
    {
        return _rom[address];
    }
    
    return _ram[address];
}

const byte * memory::impl::buffer() const
{
    return &_ram[0];
}

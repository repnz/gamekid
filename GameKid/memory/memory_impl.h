#pragma once
#include "memory.h"
#include <GameKid/io/joypad.h>
#include <vector>

class memory::impl
{
private:
    joypad _joypad;
    const std::vector<byte>& _rom;
    byte _ram[64 * 1024];

public:
    explicit impl(const std::vector<byte>& rom);
    void store(word address, byte value);
    byte load(word address);
    const byte* buffer() const;
};

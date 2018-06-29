#pragma once
#include <GameKid/cpu_types.h>

namespace memory_map {
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

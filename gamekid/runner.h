#pragma once
#include "system.h"
#include "cpu/cpu.h"
#include "cpu/instruction_set.h"
#include "cpu/opcode_decoder.h"
#include <set>
#include "gamekid.tests/test_rom_map.h"

namespace gamekid {

    class runner {
    private:
        rom::cartridge _cart;
        io::video::lcd _lcd;
        std::unique_ptr<rom::rom_map> _rom_map;
        memory::gameboy_memory_map _memory_map;
        system _system;
        cpu::instruction_set _set;
        cpu::opcode_decoder _decoder;
        std::set<word> _breakpoints;
    public:
        explicit runner(rom::cartridge&& rom);

        std::vector<std::string> list(int count);
        void add_breakpoint(word address);
        void run_until_break();
        void next();
        void run();
        cpu::cpu& cpu();
    };

}

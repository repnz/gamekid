#include "runner.h"
#include <GameKid/cartridge.h>

runner::runner(std::vector<byte>&& rom) :
    _rom(std::move(rom)), _set(_cpu), _decoder(_set)
{
    cartridge::validate_header_checksum(_rom.data());
    
    if (_rom.size() > 0xFFFF) 
    {
        throw "OverflowError";
    }

    word rom_size_word = static_cast<word>(_rom.size());

    for (word i = 0; i < rom_size_word; ++i) 
    {
        _cpu.mem.store_byte(i, _rom[i]);
    }
}

void runner::add_breakpoint(word address)
{
    _breakpoints.insert(address);
}

void runner::run_until_break()
{
    while (_breakpoints.find(_cpu.PC) == _breakpoints.end())
    {
        next();
    }
}

void runner::next()
{
    opcode* opcode = _decoder.decode(_cpu.mem.buffer() + _cpu.PC);

    if (opcode == nullptr) 
    {
        throw "InvalidOpcode";
    }

    opcode->run();
    _cpu.PC += opcode->full_size();
}

void runner::run()
{
    while (true)
    {
        next();
    }
}

std::vector<std::string> runner::list(int count) 
{
    std::vector<std::string> opcodes(count);
    
    word pc = _cpu.PC;

    for (int i = 0; i < count; i++)
    {
        const byte* buffer = _cpu.mem.buffer();
        const byte* buffer_pc = buffer + pc;
        opcode* op = _decoder.decode(buffer_pc);

        if (op == nullptr) 
        {
            const byte current_byte = *(_cpu.mem.buffer() + pc);
            opcodes[i] = ".byte " + std::to_string(current_byte);
            pc += 1;
        }
        else
        {
            const byte* immidiate_ptr = _cpu.mem.buffer() + pc + op->size();
            opcodes[i] = op->to_str(immidiate_ptr);
            pc += op->full_size();
        }
    }

    return opcodes;
}
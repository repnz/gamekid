#include "runner.h"
#include <gamekid/rom/cartridge.h>

using namespace gamekid;

runner::runner(std::vector<byte>& rom) : _system(rom), _set(_system.cpu()), _decoder(_set){

    rom::cartridge::validate_header_checksum(rom.data());
    
    if (rom.size() > 0xFFFF) {
        throw "OverflowError";
    }

    word rom_size_word = static_cast<word>(rom.size());

    for (word i = 0; i < rom_size_word; ++i) {
        _system.memory().store_byte(i, rom[i]);
    }
}

void runner::add_breakpoint(word address){
    _breakpoints.insert(address);
}

void runner::run_until_break(){
    while (_breakpoints.find(_system.cpu().PC) == _breakpoints.end()){
        next();
    }
}

void runner::next(){
    const word opcode_word = _system.memory().load_word(_system.cpu().PC);
    gamekid::cpu::opcode* opcode = _decoder.decode(opcode_word);

    if (opcode == nullptr) {
        throw "InvalidOpcode";
    }

    opcode->run();
    _system.cpu().PC += opcode->full_size();
}

void runner::run(){
    while (true){
        next();
    }
}

std::vector<std::string> runner::list(int count) {
    std::vector<std::string> opcodes(count);
    
    word pc = _system.cpu().PC;

    for (int i = 0; i < count; i++) {
        const word opcode_word = _system.memory().load_word(pc);
        gamekid::cpu::opcode* op = _decoder.decode(opcode_word);

        if (op == nullptr)  {
            const byte current_byte = static_cast<byte>(opcode_word);
            opcodes[i] = ".byte " + std::to_string(current_byte);
            pc += 1;
        } else {
            const word imm_bytes = _system.memory().load_word(pc + op->size());
            const byte* imm_ptr = (byte*)(&imm_bytes);
            opcodes[i] = op->to_str(imm_ptr);
            pc += op->full_size();
        }
    }

    return opcodes;
}
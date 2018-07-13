#include "runner.h"
#include "rom/cartridge.h"

using namespace gamekid;

runner::runner(rom::cartridge&& cart) : 
_cart(cart), _rom_map(cart.create_rom_map()), _memory_map(*_rom_map, _lcd),
_system(_memory_map), _set(_system.cpu()), _decoder(_set){

    if (!_cart.validate_header_checksum()) {
        throw std::exception("Header checksum error");
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
        throw std::exception("InvalidOpcode");
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
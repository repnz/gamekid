#include "runner.h"
#include "rom/cartridge.h"
#include "utils/convert.h"
#include "utils/str.h"

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
    do {
        next();
    } while (_breakpoints.find(_system.cpu().PC.load()) == _breakpoints.end());
}

void runner::next(){
    const word old_pc = _system.cpu().PC.load();
    const word opcode_word = _system.memory().load_word(old_pc);
    gamekid::cpu::opcode* opcode = _decoder.decode(opcode_word);

    if (opcode == nullptr) {
        throw std::exception("InvalidOpcode");
    }

    _system.cpu().PC.store(old_pc + opcode->full_size());
    opcode->run();
}

void runner::run(){
    while (true){
        next();
    }
}

cpu::cpu& runner::cpu() {
    return _system.cpu();
}

std::vector<byte> runner::dump(word address_to_view, word length_to_view) {
    std::vector<byte> bytes(length_to_view);

    for (int i = 0; i < length_to_view; ++i) {
        bytes[i] = _system.memory().load<byte>(address_to_view+i);
    }

    return bytes;
}

void runner::delete_breakpoint(word breakpoint_address) {
    auto addr_iter = _breakpoints.find(breakpoint_address);

    if (addr_iter == _breakpoints.end()) {
        throw std::exception("Breakpoint does not exist in that address");
    }

    _breakpoints.erase(addr_iter);
}

std::vector<std::string> runner::list(word address, word count) {
    std::vector<std::string> opcodes(count);
    
    for (word i = 0; i < count; i++) {
        const word opcode_word = _system.memory().load_word(address);
        gamekid::cpu::opcode* op = _decoder.decode(opcode_word);

        // Write the address 
        opcodes[i] = utils::convert::to_hex(address) + "  ";

        if (op == nullptr)  {
            // opcode was not found, write byte value
            const byte current_byte = static_cast<byte>(opcode_word);
            opcodes[i] += utils::convert::to_hex<byte>(current_byte);
            opcodes[i] += "          .byte";
            address += 1;
        } else {
            // calculate the immidiate values of the opcode
            const word imm_bytes = _system.memory().load_word(address + static_cast<word>(op->size()));
            const byte* imm_ptr = (byte*)(&imm_bytes);

            // add opcode bytes 
            for (byte b : op->full_opcode(imm_ptr)) {
                opcodes[i] += utils::convert::to_hex<byte>(b) + ' ';
            }

            // add padding
            opcodes[i] += std::string(12 - op->full_size() * 3 + 1, ' ');

            // add opcode mnemonic
            opcodes[i] += op->to_str(imm_ptr);
            address += op->full_size();
        }
    }

    return opcodes;
}

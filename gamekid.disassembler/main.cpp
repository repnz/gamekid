#include <gamekid/system.h>
#include <gamekid/cpu/opcode_decoder.h>
#include <gamekid/utils/files.h>
#include <gamekid/utils/bytes.h>

#include <iostream>

int main(int argc, const char** argv){    
    if (argc < 2){
        std::cerr << "Missing filename argument";
        return -1;
    }
    
    std::vector<byte> opcodes = gamekid::utils::files::read_file(argv[1]);
    const byte* opcode_ptr = opcodes.data();

    gamekid::system system({});
    gamekid::cpu::instruction_set s(system.cpu());
    gamekid::cpu::opcode_decoder d(s);
    
    for (size_t i=0; i<opcodes.size();) {
        const word opcode_word = gamekid::utils::bytes::read_value<word>(opcode_ptr + i);
        const gamekid::cpu::opcode* op = d.decode(opcode_word);

        if (op == nullptr) {
            std::cout << ".byte " << std::hex << (int)opcode_ptr[i] << std::endl;
            i += 1;
        } else {
            const byte* immidiate_ptr = opcode_ptr + i + op->size();
            std::cout << std::hex << i << " " << op->to_str(immidiate_ptr) << std::endl;
            i += op->full_size();
        }
    }

    return 0;
}
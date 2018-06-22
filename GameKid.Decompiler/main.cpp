#include <GameKid/cpu/opcode_decoder.h>
#include <GameKid/utils/files.h>
#include <iostream>

int main(int argc, const char** argv)
{    
    if (argc < 2)
    {
        std::cerr << "Missing filename argument";
        return -1;
    }
    
    std::vector<byte> opcodes = files::read_file(argv[1]);
    const byte* opcode_ptr = opcodes.data();

    cpu cpu;
    instruction_set s(cpu);
    opcode_decoder d(s);
    
    for (size_t i=0; i<opcodes.size();)
    {
        const opcode* op = d.decode(opcode_ptr+i);

        if (op == nullptr)
        {
            std::cout << ".byte " << std::hex << (int)opcode_ptr[i] << std::endl;
            i += 1;
        }
        else
        {
            const byte* immidiate_ptr = opcode_ptr + i + op->size();
            std::cout << std::hex << i << " " << op->to_str(immidiate_ptr) << std::endl;
            i += op->full_size();
        }
    }

    return 0;
}
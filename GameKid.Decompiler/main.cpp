#include <GameKid/cpu/opcode_decoder.h>
#include <iostream>
#include <fstream>

int main(int argc, const char** argv)
{    
    std::cout << "GameKidDecompiler" << std::endl;

    cpu cpu;
    instruction_set s(cpu);
    opcode_decoder d(s);

    if (argc < 2)
    {
        std::cerr << "Missing filename argument";
        return -1;
    }

    std::string fileName(argv[1]);
    std::ifstream f(fileName, std::ios::binary | std::ios::in | std::ios::ate);
    int file_size = f.tellg();
    f.seekg(std::ios::beg);
    std::vector<byte> opcodes(file_size);
    f.read((char*)opcodes.data(), file_size);
    
    const byte* opcode_ptr = opcodes.data();
    
    for (int i=0; i<file_size;)
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

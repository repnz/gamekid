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
    std::ifstream f(fileName, std::ios::binary | std::ios::in);
    byte* opcodes = new byte[1024 * 1024];
    f.read((char*)opcodes, 1024 * 1024);
    byte* opcode_ptr = &opcodes[0];
    
    while (f.eof())
    {
        opcode* op = d.decode(opcode_ptr);

        if (op == nullptr)
        {
            std::cout << "ERR" << std::endl;
            opcode_ptr += 1;

        }
        else
        {
            int opcode_size = op->size();
            std::cout << op->to_str(opcode_ptr + opcode_size) << std::endl;
            opcode_ptr += opcode_size;
        }
    }

    
}

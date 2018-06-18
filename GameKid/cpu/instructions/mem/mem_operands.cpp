#include "mem_operands.h"

std::vector<byte> immidiate_bytes(const std::string& operand, int size_in_bytes)
{
    int parsed = stoi(operand);

    const int size_in_bits = (1 << (size_in_bytes * 8));

    if (parsed >= size_in_bits)
    {
        throw std::exception("Operand value exeeds");
    }

    std::vector<byte> v(size_in_bytes);

    for (byte i = 0; i<size_in_bytes; ++i)
    {
        v[i] = (parsed & 0xFF);
        parsed >>= 8;
    }

    return v;
}

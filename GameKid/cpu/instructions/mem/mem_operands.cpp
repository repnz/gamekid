#include "mem_operands.h"
#include <GameKid/utils/bytes.h>

std::vector<byte> immidiate_bytes(const std::string& operand, int size_in_bytes)
{
    int parsed = stoi(operand);

    const int size_in_bits = (1 << (size_in_bytes * 8));

    if (parsed >= size_in_bits)
    {
        throw std::exception("Operand value exeeds");
    }

    return bytes::little_endian_encode(parsed, size_in_bytes);
}

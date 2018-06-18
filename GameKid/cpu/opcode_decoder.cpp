#include "opcode_decoder.h"
#include <memory>
#include <set>
#include <GameKid/utils/bytes.h>

opcode_decoder::opcode_decoder(instruction_set & set)
    : _set(set)
{
    initialize_tables();
}

void opcode_decoder::initialize_tables()
{
    for (instruction* instruction : _set.instructions())
    {
        for (opcode* op : *instruction)
        {
            const word opcode_word_value = bytes::little_endian_decode<word>(op->value);
            _opcode_table.insert(std::pair<word, opcode*>(opcode_word_value, op));
        }
    }
}

opcode* opcode_decoder::decode(const byte* bytes)
{
    const word opcode_word = *(word*)bytes;

    auto one_byte_opcode = _opcode_table.find(opcode_word & 0xFF);

    if (one_byte_opcode != _opcode_table.end())
    {
        return one_byte_opcode->second;
    }

    auto two_bytes_opcode = _opcode_table.find(opcode_word);

    if (two_bytes_opcode != _opcode_table.end())
    {
        return two_bytes_opcode->second;
    }

    return nullptr;
}

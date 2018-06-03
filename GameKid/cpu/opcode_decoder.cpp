#include "opcode_decoder.h"
#include <memory>
#include <set>

opcode_decoder::opcode_decoder(instruction_set & set)
    : _set(set)
{
    initialize_tables();
}

void opcode_decoder::initialize_tables()
{
    for (instruction* instruction : _set.instructions())
    {
        for (opcode* op : instruction->opcodes())
        {
            if (op->value[0] == 0xCB)
            {
                _cb_prefix_table[op->value[1]] = op;
            }
            else
            {
                _main_table[op->value[0]] = op;
            }
        }
    }
}

opcode* opcode_decoder::decode(byte* bytes)
{
    std::map<byte, opcode*>* correct_table;

    if (bytes[0] == 0xCB)
    {
        correct_table = &_cb_prefix_table;
        bytes++;
    }
    else
    {
        correct_table = &_main_table;
    }
    auto opcode_key = correct_table->find(bytes[0]);

    if (opcode_key == _cb_prefix_table.end())
    {
        return nullptr;
    }

    return opcode_key->second;
}

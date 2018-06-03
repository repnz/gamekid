#include <memory>
#include "instruction_builder.h"
#include <GameKid/cpu/instruction.h>

std::unique_ptr<instruction> instruction_builder::build()
{
    std::unique_ptr<instruction> ins = std::make_unique<instruction>(_cpu, _name);

    for (auto& b : _byte_opcode_builders)
    {
        ins->add_opcode(b.build());
    }

    for (auto& b : _byte_opcode_builders)
    {
        ins->add_opcode(b.build());
    }

    return std::move(ins);
}


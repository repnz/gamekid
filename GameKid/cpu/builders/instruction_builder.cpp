#include <memory>
#include "instruction_builder.h"
#include <GameKid/cpu/instruction.h>

instruction_builder::instruction_builder(cpu& cpu, const std::string& name): 
_cpu(cpu),
builded_instruction(std::make_unique<instruction>(cpu, name))
{
}

void instruction_builder::add_opcode(std::unique_ptr<opcode> opcode)
{
    builded_instruction->add_opcode(std::move(opcode));
}

std::unique_ptr<instruction> instruction_builder::build()
{
    return std::move(builded_instruction);
}


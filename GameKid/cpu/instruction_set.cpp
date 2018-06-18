#include <GameKid/cpu/instruction_set.h>
#include <GameKid/cpu/instructions/alu.h>
#include <GameKid/cpu/instructions/rotation.h>
#include <GameKid/cpu/instructions/bitmask.h>
#include <GameKid/cpu/instructions/misc.h>
#include "instructions/mem.h"
#include "instructions/jumps.h"


instruction_set::instruction_set(cpu& cpu) : _cpu(cpu)
{
    misc::initialize(cpu, *this);
    
    alu alu(*this, cpu);
    alu.initialize();

    mem::initialize(cpu, *this);

    bitmask bitmask(cpu, *this);
    bitmask.initialize();

    rotation::initialize(*this, cpu);
    jumps::initialize(cpu, *this);
}

void instruction_set::add_instruction(std::unique_ptr<instruction> ins)
{
    _ptr_instructions.push_back(ins.get());
    _instructions.push_back(std::move(ins));
}

const std::vector<instruction*>& instruction_set::instructions()
{
    return _ptr_instructions;
}

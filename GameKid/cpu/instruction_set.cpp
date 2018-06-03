#include <GameKid/cpu/instruction_set.h>
#include <GameKid/cpu/instructions/alu_8.h>
#include <GameKid/cpu/instructions/rotation.h>
#include <GameKid/cpu/instructions/bitmask.h>
#include <GameKid/cpu/instructions/misc.h>
#include "instructions/mem.h"
#include "instructions/jumps.h"


instruction_set::instruction_set(cpu& cpu) : _cpu(cpu), 
_misc(cpu, *this), _alu(*this, cpu), _mem(cpu, *this), _bitmask(cpu, *this)
{
    _misc.initialize();
    _alu.initialize();
    _mem.initialize();
    _bitmask.initialize();
    rotation::initialize(*this, cpu);
    jumps::initialize(cpu, *this);
}

void instruction_set::add_instruction(std::unique_ptr<instruction> instruction)
{
    _ptr_instructions.push_back(instruction.get());
    _instructions.push_back(std::move(instruction));
}

const std::vector<instruction*>& instruction_set::instructions()
{
    return _ptr_instructions;
}

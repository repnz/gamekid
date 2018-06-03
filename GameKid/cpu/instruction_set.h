#pragma once
#include <vector>
#include <GameKid/cpu/instruction.h>
#include <memory>
#include "instructions/alu_8.h"
#include "instructions/mem.h"
#include "instructions/bitmask.h"
#include "instructions/misc.h"


class instruction_set
{
private:
    std::vector<std::unique_ptr<instruction>> _instructions;
    std::vector<instruction*> _ptr_instructions;
    alu_8 _alu;
    mem _mem;
    bitmask _bitmask;
    misc _misc;
public:
    cpu & _cpu;
    const std::vector<instruction*>& instructions();
    explicit instruction_set(cpu& cpu);

    void add_instruction(std::unique_ptr<instruction> instruction);
};

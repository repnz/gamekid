#pragma once
#include <GameKid/cpu/instruction.h>
#include "GameKid/cpu/base_instructions/single_opcode_instruction.h"
#include "GameKid/opcodes.h"

class scf_instruction : public single_opcode_instruction
{
public:
    explicit scf_instruction(cpu& cpu)
        : single_opcode_instruction(cpu, "scf", SCF, false, 4)
    {
    }

    void run() override
    {
        _cpu.scf();
    }
};

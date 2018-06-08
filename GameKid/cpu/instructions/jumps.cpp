#include "jumps.h"
#include <GameKid/cpu.h>
#include <GameKid/cpu/instruction_set.h>
#include <GameKid/cpu/operands.h>

void jump_absolute_operation(cpu& cpu, operand<word>& address)
{
    cpu.jump(address.load());
}

void jumps::initialize(cpu & cpu, instruction_set & set)
{
    set.add_instruction(instruction_builder(cpu, "jp")
        .operands(cpu.operands().immidiate_word())
            .opcode(0xC3)
            .cycles(12)
            .operation(jump_absolute_operation)
            .add()
        .build());
}

#include "jumps.h"
#include <GameKid/cpu.h>
#include <GameKid/cpu/instruction_set.h>
#include <GameKid/cpu/operands.h>

void jumps::initialize(cpu & cpu, instruction_set & set)
{
    set.add_instruction(
        instruction_builder(cpu).name("jp")
        .operands(cpu.operands().immidiate_word())
            .opcode(0xC3).cycles(12).operation([&cpu](operand<word>& address)
            {
                cpu.jump(address.load());
            }).add()
        .build());
}

#include <GameKid/cpu/instructions/misc.h>
#include <GameKid/cpu/builders/instruction_builder.h>
#include <GameKid/cpu/operands.h>
#include "GameKid/cpu/base_instructions/single_opcode_instruction.h"
#include "GameKid/opcodes.h"
#include "GameKid/cpu/instruction_set.h"


void misc::initialize()
{
    _set.add_instruction(instruction_builder(_cpu).name("swap")
        .operands(_cpu.A).opcode(CB_PREFIX, SWAP_A).cycles(8).add()
        .operands(_cpu.B).opcode(CB_PREFIX, SWAP_A).cycles(8).add()
        .operands(_cpu.C).opcode(CB_PREFIX, SWAP_A).cycles(8).add()
        .operands(_cpu.D).opcode(CB_PREFIX, SWAP_A).cycles(8).add()
        .operands(_cpu.E).opcode(CB_PREFIX, SWAP_A).cycles(8).add()
        .operands(_cpu.H).opcode(CB_PREFIX, SWAP_A).cycles(8).add()
        .operands(_cpu.L).opcode(CB_PREFIX, SWAP_A).cycles(8).add()
        .operands(_cpu.operands().reg_mem(_cpu.HL)).opcode(CB_PREFIX, SWAP_A).cycles(8).add()
        .operation<byte>([this](operand<byte>& op)
        {
            byte val = op.load();
            _cpu.swap(&val);
            op.store(val);
        })
        .build());

    _set.add_instruction(std::make_unique<single_opcode_instruction>(
        _cpu,
        "cpl",
        std::vector<byte> {0x2f},
        4,
        [this]()
        {
            _cpu.A.store(~_cpu.A.load());
            _cpu.half_carry_flag = 1;
            _cpu.substruct_flag = 1;
        }
    ));

    _set.add_instruction(std::make_unique<single_opcode_instruction>(
        _cpu,
        "nop",
        std::vector<byte> {NOP},
        4,
        [this](){ } // do nothing 
    ));

    _set.add_instruction(std::make_unique<single_opcode_instruction>(
        _cpu,
        "scf",
        std::vector<byte> {SCF},
        4,
        [this]() { _cpu.scf(); }
    ));

    _set.add_instruction(std::make_unique<single_opcode_instruction>(
        _cpu,
        "stop",
        std::vector<byte> {0x10, 0x0},
        4,
        [this]() { _cpu.stop(); } 
    ));

    _set.add_instruction(std::make_unique<single_opcode_instruction>(
            _cpu,
            "daa",
            std::vector<byte> {0x27},
            4,
            [this]()
            {
                const byte left_digit = (_cpu.A.load() & 0xF0) >> 4;
                const byte right_digit = (_cpu.A.load() & 0x0F);

                if (left_digit > 10 || right_digit > 10)
                {
                    // Error, what to do?
                }

                _cpu.A.store(left_digit * 10 + right_digit);
                _cpu.set_zero_flag(_cpu.A.load());
                _cpu.substruct_flag = 0;
                // what should be done with the carry flag?
            }
        ));
}

#include "register_instruction.h"

register_instruction::register_instruction(cpu& cpu, std::string name,
    bool cb_prefix,
    const register_opcode_values& values) : instruction(cpu, name)
{
    _operation = [this](byte* addr) { run(addr); };
    byte cycles = (cb_prefix) ? 4 : 8;

    add_register_opcode(values.A, cpu.regs.A, cb_prefix, cycles);
    add_register_opcode(values.B, cpu.regs.B, cb_prefix, cycles);
    add_register_opcode(values.C, cpu.regs.C, cb_prefix, cycles);
    add_register_opcode(values.D, cpu.regs.D, cb_prefix, cycles);
    add_register_opcode(values.E, cpu.regs.E, cb_prefix, cycles);
    add_register_opcode(values.H, cpu.regs.H, cb_prefix, cycles);
    add_register_opcode(values.L, cpu.regs.L, cb_prefix, cycles);
}

std::vector<byte> register_instruction::parse(const std::vector<std::string>& operands)
{
    if (operands.size() != 1)
    {
        return {};
    }

    const std::string& register_name = operands[0];

    auto it = _register_opcodes.find(register_name);

    if (it == _register_opcodes.end())
    {
        return {};
    }

    return it->second.bytes();
}

void register_instruction::add_register_opcode(const byte value,
    const reg& reg, bool cb_prefix, byte cycles)
{
    _register_opcodes.insert(std::make_pair(reg.name, register_opcode(
        _cpu,
        name,
        value,
        _operation,
        reg,
        cb_prefix,
        cycles
    )));

    opcodes.push_back(&_register_opcodes.at(reg.name));
}

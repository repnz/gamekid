#include "GameKid/cpu_types.h"
#include <string>
#include "GameKid/cpu.h"
#include "bitmask_instruction.h"
#include <sstream>
#include "GameKid/cpu/base_opcodes/register_opcode.h"

bitmask_opcode::bitmask_opcode(cpu& cpu, const std::string& name, 
    byte base_value, reg8& reg,
    std::function<void(byte*, byte)> operation, byte bit) :
    opcode(cpu, name, base_value + (bit * 8), true, 8),
    _bit(bit), _operation(operation), _register(reg)
{
}

void bitmask_opcode::run()
{
    _operation(_register.address(), _bit);
}

std::string bitmask_opcode::to_str(byte* next)
{
    std::ostringstream ss;
    ss << name << " " << _bit << ", " << _register.name();
    return ss.str();
}

bitmask_instruction::bitmask_instruction(cpu& cpu,
    const std::string& name, const register_opcode_values& values) :
    instruction(cpu, name)
{
    _operation = [this](byte* address, byte bit) { this->run(address, bit); };

    add_register_opcodes(cpu.A, values.A);
    add_register_opcodes(cpu.B, values.B);
    add_register_opcodes(cpu.C, values.C);
    add_register_opcodes(cpu.D, values.D);
    add_register_opcodes(cpu.E, values.E);
    add_register_opcodes(cpu.H, values.H);
    add_register_opcodes(cpu.L, values.L);
}

std::vector<byte> bitmask_instruction::parse(const std::vector<std::string>& operands)
{
    const int bit = atoi(operands[0].c_str());

    if (bit < 0 || bit > 7) { return {}; }

    const std::string& reg = operands[1];

    return _bit_opcodes[reg][bit].bytes();
}

void bitmask_instruction::add_register_opcodes(reg8& r, byte base_value)
{
    std::vector<bitmask_opcode>& register_map = _bit_opcodes[r.name()];

    for (byte bit = 0; bit < 8; ++bit)
    {
        register_map.push_back(
            bitmask_opcode(
                _cpu,
                name,
                base_value,
                r,
                _operation,
                bit
            )
        );

        opcodes.push_back(&register_map.back());
    }
}

#include "GameKid/cpu_types.h"
#include <string>
#include "GameKid/cpu.h"
#include "bitmask_instruction.h"
#include <sstream>

void bitmask_opcode::run()
{
	_operation(register_address, _bit);
}

std::string bitmask_opcode::to_str(byte* next)
{
	std::ostringstream ss;
	ss << name << " " << _bit << ", " << register_name;
	return ss.str();
}

bitmask_instruction::bitmask_instruction(cpu& cpu, 
	const std::string& name, byte a, byte b, byte c,
	byte d, byte e, byte h, byte l) :
	instruction(cpu, name)
{
	_operation = [this](byte* address, byte bit) { this->run(address, bit); };

	add_register_opcodes("A", &cpu.A, a);
	add_register_opcodes("B", &cpu.B, b);
	add_register_opcodes("C", &cpu.C, c);
	add_register_opcodes("D", &cpu.D, d);
	add_register_opcodes("E", &cpu.E, e);
	add_register_opcodes("H", &cpu.H, h);
	add_register_opcodes("L", &cpu.L, l);
}

std::vector<byte> bitmask_instruction::parse(const std::vector<std::string>& operands)
{
	const int bit = atoi(operands[0].c_str());

	if (bit < 0 || bit > 7) { return {}; }

	const std::string& reg = operands[1];

	return _bit_opcodes[reg][bit].bytes();
}

void bitmask_instruction::add_register_opcodes(const std::string& register_name, byte* register_address,
                                                byte base_value)
{
	for (byte bit = 0; bit < 8; ++bit)
	{
		_bit_opcodes[register_name].push_back(
			bitmask_opcode(
				_cpu,
				name,
				base_value,
				register_name,
				register_address,
				_operation,
				bit
			)
		);
	}
}

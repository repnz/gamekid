#include "register_instruction.h"

register_instruction::register_instruction(cpu& cpu, std::string name, 
	bool cb_prefix, 
	byte a, byte b, byte c,
	byte d, byte e, byte h, byte l) : instruction(cpu, name)
{
	_operation = [this](byte* addr) { run(addr); };
	byte cycles = (cb_prefix) ? 4 : 8;

	add_register_opcode(a, "A", &cpu.A, cb_prefix, cycles);
	add_register_opcode(b, "B", &cpu.B, cb_prefix, cycles);
	add_register_opcode(c, "C", &cpu.C, cb_prefix, cycles);
	add_register_opcode(d, "D", &cpu.D, cb_prefix, cycles);
	add_register_opcode(e, "E", &cpu.E, cb_prefix, cycles);
	add_register_opcode(h, "H", &cpu.H, cb_prefix, cycles);
	add_register_opcode(l, "L", &cpu.L, cb_prefix, cycles);
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
	const std::string& register_name,
	byte* register_address, bool cb_prefix, byte cycles)
{
	_register_opcodes.insert(make_pair(register_name, register_opcode(
		_cpu,
		name,
		value,
		_operation,
		register_name,
		register_address,
		cb_prefix,
		cycles
	)));

	opcodes.push_back(&_register_opcodes.at(register_name));
}

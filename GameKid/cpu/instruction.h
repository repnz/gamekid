#pragma once
#include <array>
#include <GameKid/cpu_types.h>
#include <GameKid/cpu/opcode.h>

class instruction
{
public:
	virtual ~instruction() = default;
	std::vector<opcode*> opcodes;
	std::string name;

	explicit instruction(const std::string& name) : name(name) {}

};

class register_instruction : public instruction
{
private:
	std::array<register_opcode, 7> _arr;
public:
	register_instruction(std::string name, byte a, byte b, byte c,
		byte d, byte e, byte h, byte l) : instruction(name)
	{
		_arr[0] = register_opcode(name, { a }, run_on_byte, "A", &)
	}

	virtual void run_on_byte(cpu* cpu, byte* val) = 0;
};

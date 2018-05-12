#pragma once
#include <string>
#include "GameKid/cpu_types.h"
#include "GameKid/cpu/opcode.h"
#include "GameKid/opcodes.h"

class rrca_opcode : public opcode
{
public:
	explicit rrca_opcode(cpu& cpu)
		: opcode(cpu, "rrca", RRCA, false, 4)
	{
	}

	void run() override
	{
		_cpu.rrca();
	}
};

class rrca_instruction : public instruction
{
private:
	rrca_opcode _opcode;
public:
	explicit rrca_instruction(cpu& cpu) : instruction(cpu, "rrca"), _opcode(cpu)
	{
		opcodes.push_back(&_opcode);
	}

	std::vector<byte> parse(const std::vector<std::string>& operands) override
	{
		if (operands.size() != 0) { return {}; }

		return { _opcode.value };
	}

};

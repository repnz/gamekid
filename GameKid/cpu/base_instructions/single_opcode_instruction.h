#pragma once
#include <GameKid/cpu/instruction.h>
#include "GameKid/cpu/base_opcodes/function_opcode.h"

class single_opcode_instruction : public instruction
{
private:
	function_opcode _op;
public:
	single_opcode_instruction(cpu& cpu, const std::string& name,
		byte value, byte cb_prefix, byte cycles)
		: instruction(cpu, name), _op(cpu, name, value, cb_prefix, cycles, [this]() {run(); })
	{
		opcodes.push_back(&_op);
	}

	std::vector<byte> parse(const std::vector<std::string>& operands) override
	{
		return _op.bytes(operands);
	}

	virtual void run() = 0;
};

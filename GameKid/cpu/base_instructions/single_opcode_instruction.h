#pragma once
#include <GameKid/cpu/instruction.h>

class function_opcode : public opcode
{
private:
	std::function<void()> _function;
public:
	function_opcode(cpu& cpu, const std::string& name, byte value, 
		bool cb_prefix, std::function<void()> f)
		: opcode(cpu, name, value, cb_prefix)
	{
	}

	void run() override
	{
		_function();
	}
};
class single_opcode_instruction : public instruction
{
private:
	function_opcode _op;
public:
	single_opcode_instruction(cpu& cpu, const std::string& name,
		byte value, byte cb_prefix)
		: instruction(cpu, name), _op(cpu, name, value, cb_prefix, [this]() {run(); })
	{
		opcodes.push_back(&_op);
	}

	std::vector<byte> parse(const std::vector<std::string>& operands) override
	{
		return _op.bytes(operands);
	}

	virtual void run() = 0;
};
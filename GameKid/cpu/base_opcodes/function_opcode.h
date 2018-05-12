#pragma once
#include "GameKid/cpu/opcode.h"

class function_opcode : public opcode
{
private:
	std::function<void()> _function;
public:
	function_opcode(cpu& cpu, const std::string& name, byte value,
		bool cb_prefix, byte cycles, std::function<void()> f)
		: opcode(cpu, name, value, cb_prefix, cycles)
	{
	}

	void run() override
	{
		_function();
	}
};

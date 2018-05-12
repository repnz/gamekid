#pragma once
#include <GameKid/cpu.h>
#include <GameKid/cpu_types.h>
#include <GameKid/cpu/opcode.h>

class instruction
{
protected:
	cpu & _cpu;
	instruction(cpu& cpu, const std::string& name) : _cpu(cpu), name(name) {}
public:

	std::string name;
	std::vector<opcode*> opcodes;

	virtual ~instruction() = default;
	virtual std::vector<byte> parse(const std::vector<std::string>& operands) = 0;
};


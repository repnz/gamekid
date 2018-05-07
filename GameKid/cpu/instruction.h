#pragma once
#include <array>
#include <GameKid/cpu.h>
#include <GameKid/cpu_types.h>
#include <GameKid/cpu/opcode.h>

class instruction
{
protected:
	cpu & _cpu;
public:
	virtual ~instruction() = default;

	std::string name;
	std::vector<opcode*> opcodes;

	instruction(cpu& cpu, const std::string& name) : _cpu(cpu), name(name) {}

};

void f(cpu& cpu,
	const std::string& name,
	const std::vector<byte>& bytes,
	const std::function<void(byte* addr)>& operation,
	const std::string& register_name,
	byte* register_address)
{
}

class register_instruction : public instruction
{
private:
	register_opcode register_opcodes[7];
public:
	register_instruction(cpu& cpu, std::string name, byte a, byte b, byte c,
		byte d, byte e, byte h, byte l) : instruction(cpu, name)
	{
		std::function<void(byte*)> operation = [this](byte* addr) {run_on_byte(addr); };
	
		register_opcodes[0] = register_opcode(cpu, name, { a }, operation, "A", &cpu.A);
		register_opcodes[1] = register_opcode(cpu, name,  { b }, operation, "B", &cpu.B);
		register_opcodes[2] = register_opcode(cpu, name, { c }, operation, "C", &cpu.C);
		register_opcodes[3] = register_opcode(cpu, name, { d }, operation, "D", &cpu.D);
		register_opcodes[4] = register_opcode(cpu, name, { e }, operation, "E", &cpu.E);
		register_opcodes[5] = register_opcode(cpu, name, { h }, operation, "H", &cpu.H);
		register_opcodes[6] = register_opcode(cpu, name, { l }, operation, "L", &cpu.L);

	}

	virtual void run_on_byte(byte* val) = 0;
};

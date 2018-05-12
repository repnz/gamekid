#pragma once
#include <vector>
#include <GameKid/cpu/instruction.h>
#include <memory>


class instruction_set
{
private:
	cpu & _cpu;
	std::vector<std::unique_ptr<instruction>> _instructions;
	std::vector<instruction*> _ptr_instructions;
public:
	const std::vector<instruction*>& instructions();
	explicit instruction_set(cpu& cpu);

	template <typename T>
	void add()
	{
		_instructions.push_back(std::make_unique<T>(_cpu));
		instruction* ptr = _instructions[_instructions.size() - 1].get();
		_ptr_instructions.push_back(ptr);
	}

};

#pragma once
class cpu;
class instruction_set;

class mem
{
private:
    cpu & _cpu;
    instruction_set& _set;
public:
    mem(cpu& cpu, instruction_set& set) : _cpu(cpu), _set(set){}
    void initialize();
};

#pragma once
class instruction_set;
class cpu;

class misc
{
private:
    cpu & _cpu;
    instruction_set& _set;
public:
    misc(cpu& cpu, instruction_set& set) : _cpu(cpu), _set(set){}

    void initialize();
};

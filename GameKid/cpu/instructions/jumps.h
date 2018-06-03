#pragma once
class cpu;
class instruction_set;

class jumps
{
public:
    static void initialize(cpu& cpu, instruction_set& set);
};
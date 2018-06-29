#pragma once
#include "cpu/operand.h"
#include "cpu/operand/flags_reg8.h"
#include "cpu/operand/reg8.h"
#include "cpu/operand/reg16.h"
#include <memory>
#include <functional>
#include "cpu/builders/cpu_operation.h"
class operands;
class cpu;
#include <GameKid/cpu_types.h>
#include <GameKid/memory/memory.h>

struct scheduled_operation
{
    cpu_operation<> operation;
    int instruction_count;

    scheduled_operation(cpu_operation<> operation, int instruction_count) :
        operation(operation), instruction_count(instruction_count) {}
};

class cpu
{
private:
    byte _sp_value_low;
    byte _sp_value_high;
    std::unique_ptr<operands> _operands;
    std::vector<scheduled_operation> _scheduled_operations;
public:
    reg8 A;
    reg8 B;
    reg8 C;
    reg8 D;
    reg8 E;
    flags_reg8 F;
    reg8 H;
    reg8 L;
    reg16 AF;
    reg16 BC;
    reg16 DE;
    reg16 HL;
    reg16 SP;
    word PC;
    bool _interrupts_enabled;
    
    cpu(const std::vector<byte>& rom);
    void schedule_operation(cpu_operation<> operation, int instruction_count);
    operands& operands();
    void enable_interrupts();
    void disable_interrupts();

    memory mem;

    cpu();

    void next();
    void halt();
    void stop();
    void error();
    void run();
    ~cpu();
};
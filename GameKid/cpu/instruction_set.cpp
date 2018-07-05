#include "instruction_set.h"
#include "impl/alu.h"
#include "impl/rotation.h"
#include "impl/bitmask.h"
#include "impl/misc.h"
#include "impl/mem.h"
#include "impl/jumps.h"

using namespace gamekid::cpu;

instruction_set::instruction_set(cpu& cpu) : _cpu(cpu){
    gamekid::cpu::impl::misc::initialize(cpu, *this);
    
    impl::alu alu(*this, cpu);
    alu.initialize();
    
    impl::mem::initialize(cpu.system(), *this);

    impl::bitmask bitmask(cpu, *this);
    bitmask.initialize();

    impl::rotation::initialize(*this, cpu);
    impl::jumps::initialize(cpu, *this);
}

void instruction_set::add_instruction(std::unique_ptr<instruction> ins) {
    _ptr_instructions.push_back(ins.get());
    _instructions.push_back(std::move(ins));
}

const std::vector<instruction*>& instruction_set::instructions() {
    return _ptr_instructions;
}

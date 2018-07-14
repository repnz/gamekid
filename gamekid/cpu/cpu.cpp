#include "cpu.h"
#include "operands_container.h"

using namespace gamekid::cpu;

cpu::cpu(gamekid::system& system) :
    _system(system),
    _sp_value_low(0),
    _sp_value_high(0),
    _pc_value_low(0),
    _pc_value_high(0),
    _operands(std::make_unique<operands_container>(system)),
    A("A"),
    B("B"),
    C("C"),
    D("D"),
    E("E"),
    H("H"),
    L("L"),
    AF("AF", F.address(), A.address()),
    BC("BC", C.address(), B.address()),
    DE("DE", E.address(), D.address()),
    HL("HL", L.address(), H.address()),
    SP("SP", &_sp_value_low, &_sp_value_high),
    PC("PC", &_pc_value_low, &_pc_value_high) , _interrupts_enabled(false){
    
    regs.emplace_back(&A);
    regs.emplace_back(&B);
    regs.emplace_back(&C);
    regs.emplace_back(&D);
    regs.emplace_back(&E);
    regs.emplace_back(&F);
    regs.emplace_back(&H);
    regs.emplace_back(&L);
    regs.emplace_back(&AF);
    regs.emplace_back(&BC);
    regs.emplace_back(&DE);
    regs.emplace_back(&HL);
    regs.emplace_back(&SP);
    regs.emplace_back(&PC);
}

operands_container& cpu::operands(){
    return *_operands;
}

void cpu::enable_interrupts(){
    _interrupts_enabled = true;
}

void cpu::disable_interrupts(){
    _interrupts_enabled = false;
}

gamekid::memory::memory & cpu::memory() {
    return _system.memory();
}

gamekid::system& cpu::system() {
    return _system;
}

cpu::~cpu() = default;
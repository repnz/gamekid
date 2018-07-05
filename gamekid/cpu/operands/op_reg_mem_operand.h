#pragma once
#include <gamekid/cpu/operand.h>
#include <gamekid/memory/memory.h>
#include "reg16.h"

namespace gamekid::cpu::operands {
    class op_reg_mem_operand : public operand<byte> {
    private:
        memory::memory & _mem;
        reg16& _reg;
    public:

        reg16 & reg() { return _reg; }

        op_reg_mem_operand(memory::memory& mem, reg16& reg) : _mem(mem), _reg(reg){}

        virtual word change(word original) const = 0;

        byte load() const override {
            const word original_address = _reg.load();
            _reg.store(change(original_address));
            return _mem.load_byte(original_address);
        }

        void store(byte s) override {
            const word new_address = _reg.load();
            _reg.store(change(new_address));
            _mem.store<byte>(new_address, s);
        }

        std::string to_str(const byte* next) const override {
            return "[" + _reg.name() + "]";
        }
    };

    class inc_reg_mem_operand : public op_reg_mem_operand {
    public:
        inc_reg_mem_operand(memory::memory& mem, reg16& reg)
            : op_reg_mem_operand(mem, reg) {}

        word change(word original) const override { return original + 1; }
    };

    class dec_reg_mem_operand : public op_reg_mem_operand {
    public:
        dec_reg_mem_operand(memory::memory& mem, reg16& reg)
            : op_reg_mem_operand(mem, reg) {}

        word change(word original) const override { return original - 1; }
    };
}
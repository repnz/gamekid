#pragma once
#include <gamekid/cpu/operand.h>
#include "reg16.h"
#include <gamekid/memory/memory.h>

namespace gamekid::cpu::operands {
    class reg_mem_operand : public operand<byte> {
    private:
        memory::memory & _mem;
        reg16& _reg;
    public:
        reg16 & reg() { return _reg; }

        reg_mem_operand(memory::memory& mem, reg16& reg) : _mem(mem), _reg(reg) {}

        byte load() const override {
            return _mem.load_byte(_reg.load());
        }

        void store(byte s) override {
            _mem.store_byte(_reg.load(), s);
        }

        std::string to_str(const byte* next) const override {
            return "[" + _reg.name() + "]";
        }
    };
}
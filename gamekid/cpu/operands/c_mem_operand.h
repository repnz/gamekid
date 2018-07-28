#pragma once
#include <gamekid/cpu/cpu.h>
#include <gamekid/cpu/operand.h>
#include <gamekid/system.h>

namespace gamekid::cpu::operands {
    class c_mem_operand : public operand<byte> {
    private:
        system & _system;
    public:
        explicit c_mem_operand(system& system) : _system(system) {}

        word load_address() const {
            return _system.cpu().C.load() + 0xFF00;
        }

        byte load() const override {
            return _system.memory().load_byte(load_address());
        }

        std::string to_str(const byte* next) const override {
            return "[$FF00+c]";
        }

        void store(byte value) override {
            return _system.memory().store_byte(load_address(), value);
        }
    };
}
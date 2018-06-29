#pragma once
#include <GameKid/cpu.h>
#include <GameKid/cpu/operand.h>

class c_mem_operand : public operand<byte> {
private:
    cpu & _cpu;
public:
    explicit c_mem_operand(cpu& cpu) : _cpu(cpu) {}

    word load_address() const {
        return _cpu.C.load() + 0xFF00;
    }

    byte load() const override {
        return _cpu.mem.load_byte(load_address());
    }

    std::string to_str(const byte* next) const override {
        return "[c]";
    }

    void store(byte value) override {
        return _cpu.mem.store(load_address(), value);
    }
};

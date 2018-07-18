#pragma once
#include <gamekid/system.h>
#include <gamekid/cpu/operand.h>
#include <gamekid/cpu/cpu.h>
#include <sstream>

namespace gamekid::cpu::operands {
    class ff_offset_mem_operand : public operand<byte> {
    private:
        system& _system;
    public:
        explicit ff_offset_mem_operand(system& system) : _system(system) {}

        word load_address() const {
            return _system.cpu().immidiate<byte>() + 0xFF00;
        }

        byte load() const override {
            return _system.memory().load_byte(load_address());
        }

        std::string to_str(const byte* next) const override {
            std::stringstream ss;
            ss << "[$FF" << std::uppercase << utils::convert::to_hex<byte>(*next) << "]";
            return ss.str();
        }

        void store(byte value) override {
            return _system.memory().store(load_address(), value);
        }

        std::vector<byte> encode(const std::string& operand) const override {
            int value = std::stoi(operand);

            if (value < -128 || value >= 128)
            {
                throw std::exception("Error");
            }

            return { static_cast<byte>(value) };
        }

        int immidiate_size() const override {
            return 1;
        }
    };
}
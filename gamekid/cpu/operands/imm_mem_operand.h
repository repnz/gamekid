#pragma once
#include <gamekid/cpu/operand.h>

namespace gamekid::cpu::operands {
    template <typename T>
    class imm_mem_operand : public operand<T> {
    private:
        system & _system;
    public:
        explicit imm_mem_operand(system& system) : _system(system) {}

        word get_address() const {
            return _system.memory().load_word(_system.cpu().PC + 1);
        }

        T load() const override {
            return _system.memory().load<T>(get_address());
        }

        std::string to_str(const byte* next) const override {
            const word address = *(word*)next;
            return std::to_string(address);
        }

        void store(T value) override {
            _system.memory().store<T>(get_address(), value);
        }

        std::vector<byte> encode(const std::string& operand) const override {
            return gamekid::utils::bytes::little_endian_encode_str<word>(operand);
        }

        int immidiate_size() const override {
            return sizeof(word); // the address
        }
    };

}
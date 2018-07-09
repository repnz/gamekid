#pragma once
#include <gamekid/cpu/operand.h>

namespace gamekid::cpu::operands {
    template <typename T>
    class imm_operand : public operand<T> {
    private:
        system & _system;
    public:
        explicit imm_operand(system& system) : _system(system) {}

        T load() const override {
            return _system.memory().load<T>(_system.cpu().PC + 1);
        }

        void store(T value) override {
            throw "Cannot store";
        }

        std::string to_str(const byte* next) const override {
            T item = *(T*)next;
            return std::to_string(item);
        }

        std::vector<byte> encode(const std::string& operand) const override {
            return utils::bytes::little_endian_encode_str<T>(operand);
        }

        int immidiate_size() const override {
            return sizeof(T);
        }
    };

}


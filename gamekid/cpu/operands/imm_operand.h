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
            return _system.cpu().immidiate<T>();
        }

        void store(T) override {
            throw std::exception("Cannot store");
        }

        std::string to_str(const byte* next) const override {
            T item = *(T*)next;
            return gamekid::utils::convert::to_hex<T>(item);
        }

        std::vector<byte> encode(const std::string& operand) const override {
            return utils::bytes::little_endian_encode_str<T>(operand);
        }

        int immidiate_size() const override {
            return sizeof(T);
        }
    };

}


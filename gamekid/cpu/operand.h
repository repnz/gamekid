#pragma once
#include <string>
#include <vector>
#include <gamekid/utils/types.h>

namespace gamekid::cpu {
    template <typename T>
    class operand {
    public:
        virtual ~operand() = default;

        virtual T load() const = 0;
        virtual void store(T value) = 0;
        virtual std::string to_str(const byte* next) const = 0;

        virtual std::vector<byte> encode(const std::string& operand) const {
            return {};
        }

        virtual int immidiate_size() const {
            return 0;
        }
    };
}
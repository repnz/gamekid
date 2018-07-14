#pragma once
#include <string>

namespace gamekid::cpu {
    class reg {
    private:
        std::string _name;
        byte _size;
    public:
        explicit reg(std::string name, byte size) : _name(std::move(name)), _size(size) {
        }

        const std::string& name() const {
            return _name;
        }

        byte size() const {
            return _size;
        }

        virtual word load_as_word() const = 0;

        virtual ~reg() = default;
    };
}

#pragma once
#include <gamekid/utils/types.h>

namespace gamekid::memory {
    class cell {
    private:
        byte _value;
    public:
        cell() : _value(0) {}
        cell(cell&&) = default;
        cell& operator=(cell&&) = default;
        cell(const cell&) = delete;
        cell& operator=(const cell&) = delete;

        virtual byte load() { return _value; }
        virtual void store(byte value) { _value = value; }
        virtual ~cell() = default;
    };
}
#pragma once
#include "cell.h"
#include <exception>

namespace gamekid::memory {
    class readonly_cell : public cell {

    public:
        void store(byte value) override {
            throw std::exception("Cannot Store");
        }
    };
}

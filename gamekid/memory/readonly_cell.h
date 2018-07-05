#pragma once
#include "cell.h"

namespace gamekid::memory {
    class readonly_cell : public cell {

    public:
        void store(byte value) override {
            throw "Cannot Store";
        }
    };
}
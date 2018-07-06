#pragma once
#include "page.h"
#include <array>
#include "cell.h"

namespace gamekid::memory {
    class normal_page : public page {
    private:
        std::array<cell, 256> _cells;
    public:
        byte load(byte offset) override {
            return _cells[offset].load();
        }

        void store(byte offset, byte value) override {
            _cells[offset].store(value);
        }
    };
}

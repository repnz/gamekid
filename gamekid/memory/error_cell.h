#pragma once
#include "cell.h"
#include <exception>

namespace gamekid::memory {
    class error_cell : public cell {
    private:
        error_cell() = default;
    public:
        error_cell(const error_cell&) = delete;
        
        static error_cell& instance() {
            static error_cell _instance;
            return _instance;
        }

        byte load() override {
            throw std::exception("Cannot load from cell");
        }

        void store(byte value) override {
            throw std::exception("Error. Cannot store to cell");
        }
    };
}

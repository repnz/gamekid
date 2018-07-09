#pragma once
#include "page.h"
#include <exception>

namespace gamekid::memory {
    class error_page : public page {
    private:
        error_page() = default;
    public:
        error_page(const error_page&) = delete;
        error_page& operator=(const error_page&) = delete;

        static error_page& instance() {
            static error_page _instance;
            return _instance;
        }

        byte load(byte offset) override {
            throw std::exception("Cannot load from error page");
        }

        void store(byte offset, byte value) override {
            throw std::exception("Cannot store to error page");
        }
    };
}

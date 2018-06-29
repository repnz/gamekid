#pragma once
#include <string>

namespace convert {

    int to_number(const std::string& str, int byte_size, int base = 10);

    template <typename T>
    inline T to_number(const std::string& str, int base = 10) {
        return static_cast<T>(to_number(str, sizeof(T), base));
    }
}
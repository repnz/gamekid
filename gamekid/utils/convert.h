#pragma once
#include <string>
#include <sstream>
#include <iomanip>

namespace gamekid::utils::convert {

    int to_number(const std::string& str, int byte_size, int base = 10);

    template <typename T>
    T to_number(const std::string& str, int base = 10) {
        return static_cast<T>(to_number(str, sizeof(T), base));
    }

    template <typename T>
    std::string to_hex(T value, int width = sizeof(T)*2) {
        std::stringstream ss;
        ss << std::setfill('0') << std::setw(width) << std::hex << value;
        return ss.str();
    }
}

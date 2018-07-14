#include "convert.h"
#include <sstream>

int gamekid::utils::convert::to_number(const std::string& str, int byte_size, int base) {

    int parsed = std::stoi(str, nullptr, base);

    const int max_number = (1 << (byte_size * 8));

    if (parsed > max_number) {
        throw std::exception("Operand value exeeds");
    }

    return parsed;
}

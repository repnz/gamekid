#pragma once

namespace gamekid::utils {
    struct offset {
        size_t start;
        size_t length;

        offset(int start, int length) : start(start), length(length) {}
    };
}


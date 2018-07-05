#pragma once

namespace gamekid::utils {
    struct offset {
        int start;
        int length;

        offset(int start, int length) : start(start), length(length) {}
    };
}

